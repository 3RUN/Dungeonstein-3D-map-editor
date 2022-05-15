
float4x4 matWorldViewProj;
float4x4 matWorld;
float4x4 matTexture;

float iLights;
float4 vecLightPos[8];
float4 vecLightColor[8];
float4 vecLightDir[8];

float4 vecViewPos;
float4 vecViewDir;
float4 vecFog;
float4 vecFogColor;
float4 vecLight;
float4 vecColor;
float4 vecAmbient;
float4 vecEmissive;
float4 vecTime;
float4 vecSkill1;
float4 vecSkill41;

texture entSkin1;

sampler ColorSampler = sampler_state
{
	Texture = <entSkin1>;
	Mipfilter = None;
	Minfilter = None;
	Magfilter = None;
};

void VS(
in float4 inposition : POSITION,
in float3 innormal : NORMAL,
in float4 intex1 : TEXCOORD0,
in float4 intex2 : TEXCOORD1,
out float4 outposition : POSITION,
out float4 outcolor : COLOR0,
out float3 outnormal : TEXCOORD0,
out float4 outtex : TEXCOORD1,
out float4 outworldPos : TEXCOORD2)
{
	inposition.w = 1.0f;
	
	// vertex snapping
	float4 snapToPixel = mul(inposition, matWorldViewProj);
	float4 vertex = snapToPixel;
	vertex.xyz = snapToPixel.xyz / snapToPixel.w;
	vertex.x = floor((vecSkill1.y + 40) * vertex.x) / (vecSkill1.y + 40); // default 160
	vertex.y = floor(vecSkill1.y * vertex.y) / vecSkill1.y; // default 120
	vertex.xyz *= snapToPixel.w;
	outposition = vertex;
	
	outnormal = normalize(mul(innormal, (float3x3)matWorld));

	float fCycle = vecTime.w * vecSkill41.y * 0.1;
	float fAmp = vecSkill41.x * 0.001;
	float fMod = 1 + vecSkill41.z;
	
	outtex.x = intex1.x + fAmp * sin(intex1.y * fMod + fCycle)+float2(matTexture._m20,matTexture._m21);
	outtex.y = intex1.y - fAmp * sin(intex1.x * fMod + fCycle)+float2(matTexture._m20,matTexture._m21);
	outtex.zw = intex2.xy+float2(matTexture._m20,matTexture._m21);
	outworldPos = mul(inposition, matWorld);

	outcolor = float4(1, 1, 1, 1);

	// vertex lightning
	if(vecSkill1.w > 0)
	{
		outcolor = float4(vecColor.xyz, vecLight.w);
	
		float light = 0;
		if(vecSkill1.z <= 0){ vecSkill1.z = 1; } // make sure we do have lights at all !
		for(light = 0; light < iLights; light += 1.0)
		{
			// light ray
			float3 ray = outworldPos - vecLightPos[light].xyz;
		
			// spotlight factor
			float depth = saturate(dot(vecLightDir[light].xyz, ray) / vecLightPos[light].w);
			float spot = 1.0 - saturate(length(cross(vecLightDir[light].xyz, ray)) / (vecLightPos[light].w * depth));
		
			// normalize the light ray
			float dist = length(ray);
			ray /= dist; 
		
			// attenuation
			float att = 1.0 - saturate(dist / vecLightPos[light].w);
		
			// final light factor
			float strength = vecLightDir[light].w ? spot * att : att;
		
			// diffuse term
			outcolor.rgb += vecLightColor[light].rgb * saturate(-dot(ray, outnormal.xyz)) * strength * vecSkill1.z;
		}

		if(vecSkill41.w > 0)
		{
			outcolor.rgb += 0.1;
		}
	}
	
	outcolor.rgb = clamp(outcolor.rgb, 0.004, 255); // 1 ... 255
	outcolor.rgb = saturate(outcolor.rgb);
	outcolor.rgb = pow(outcolor.rgb, vecSkill1.x); // adjustable brightness
}

float4 PS(
float4 color : COLOR0,
float3 normal : TEXCOORD0,
float4 tex : TEXCOORD1,
float4 worldPos : TEXCOORD2) : COLOR0
{
	normal.xyz = normalize(normal.xyz);
	
	float4 textureColor = tex2D(ColorSampler, tex.xy);
	
	color.rgb *= textureColor.rgb;
	
	float fDepth = distance ( vecViewPos.xyz, worldPos.xyz );
	float Fog = saturate ( ( fDepth - vecFog.x ) * vecFog.z );
	color.rgb = lerp ( color.rgb, vecFogColor, Fog );
	
	color.a = 1;

	// if color is black (RGB < 8, 8, 8)
	// then make invisible !
	if(textureColor.r < 0.031 && textureColor.g < 0.031 && textureColor.b < 0.031)
	{
		color.rgb = 0;
		color.a = 0;
	}
	
	return color;
}

technique
{
	pass pass0
	{
		VertexShader = compile vs_3_0 VS(); 
		PixelShader  = compile ps_3_0 PS(); 
	}
}

technique fallback { pass one { } }