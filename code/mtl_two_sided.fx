
float4x4 matWorldViewProj;
float4x4 matWorld;

float4 vecViewPos;
float4 vecViewDir;
float4 vecFog;
float4 vecFogColor;
float4 vecLight;
float4 vecColor;
float4 vecAmbient;
float4 vecEmissive;

float4 vecSkill1;

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
    outposition = mul(inposition, matWorldViewProj);	
	outnormal = normalize(mul(innormal, (float3x3)matWorld));
	outtex.xy = intex1.xy;
	outtex.zw = intex2.xy;
	outworldPos = mul(inposition, matWorld);

	outcolor = (vecAmbient * vecLight) + float4(vecEmissive.xyz * vecColor.xyz, vecLight.w);

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
	
	float3 vPixelToViewDir = normalize(vecViewPos.xyz - worldPos.xyz);
	float dot_result = dot(vPixelToViewDir, normal.xyz);
	color.rgb *= saturate(1.0 - (1.0 - abs(dot_result)) * vecSkill1.y);	
	
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
		CullMode = None;
		//ZWriteEnable = True;
		//AlphaBlendEnable = False;
		//AlphaTestEnable = False;
		
		VertexShader = compile vs_1_0 VS(); 
		PixelShader  = compile ps_1_0 PS(); 
	}
}

technique fallback { pass one { } }