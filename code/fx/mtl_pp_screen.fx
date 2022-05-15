// FROM
// https://www.shadertoy.com/view/tlc3DM

// ported to shaderToy by László Matuska / @BitOfGold
// from here: https://github.com/jmickle66666666/PSX-Dither-Shader/blob/master/PSX%20Dither.shader
// uses Shadertoy's 8x8 bayer dithering pattern instead of the original pattern

// vignette from: https://www.shadertoy.com/view/MsXGD4
// original from: https://www.shadertoy.com/view/XdyGzR

#define CURVATURE
#define SCANLINES
#define CURVED_SCANLINES
#define BLURED
#define LIGHT
#define COLOR_CORRECTION
//#define VIGNETTE

// Number of colors. 32 (5 bits) per channel
const float3 _Colors = float3(32.0, 32.0, 32.0);

const float4 vecTime;
const float4 vecViewPort;

const float gamma = 1;
const float contrast = 1;
const float saturation = 1;
const float brightness = 1;

const float light = 9;
const float blur = 1.5;

texture TargetMap;
texture mtlSkin1;

sampler postTex = sampler_state
{
	texture = <TargetMap>;
	MinFilter = Linear;
	MagFilter = Linear;
	MipFilter = Linear;  
	AddressU = Clamp;
	AddressV = Clamp;
};

sampler noiseTex = sampler_state
{
	texture = <mtlSkin1>;
	MinFilter = linear; 
	MagFilter = linear; 
	MipFilter = linear; 
	AddressU = Wrap;
	AddressV = Wrap;
};

float channelError(float col, float colMin, float colMax)
{
	float range = abs(colMin - colMax);
	float aRange = abs(col - colMin);
	return aRange /range;
}

float ditheredChannel(float error, float2 ditherBlockUV)
{
	float pattern = tex2D(noiseTex, ditherBlockUV).r;
	if(error > pattern)
	{
		return 1.0;
	}
	else
	{
		return 0.0;
	}
}

float4 mix(float4 a, float4 b, float amt)
{
	return((1.0 - amt) * a) + (b * amt);
}

/// YUV/RGB color space calculations
float3 RGBtoYUV(float3 rgb)
{
	float3 yuv;
	yuv.r = rgb.r * 0.2126 + 0.7152 * rgb.g + 0.0722 * rgb.b;
	yuv.g = (rgb.b - yuv.r) / 1.8556;
	yuv.b = (rgb.r - yuv.r) / 1.5748;

	yuv.gb += 0.5;
	return yuv;
}

float3 YUVtoRGB(float3 yuv)
{
	yuv.gb -= 0.5;
	return float3(
	yuv.r * 1.0 + yuv.g * 0.0 + yuv.b * 1.5748,
	yuv.r * 1.0 + yuv.g * -0.187324 + yuv.b * -0.468124,
	yuv.r * 1.0 + yuv.g * 1.8556 + yuv.b * 0.0);
}

float3 ditherColor(float3 col, float2 uv, float xres, float yres)
{
	float3 yuv = RGBtoYUV(col);

	float3 col1 = floor(yuv * _Colors) / _Colors;
	float3 col2 = ceil(yuv * _Colors) / _Colors;
	
	// Calculate dither texture UV based on the input texture
	float2 ditherBlockUV = uv * float2(xres / 16.0, yres / 16.0);
	
	yuv.x = mix(col1.x, col2.x, ditheredChannel(channelError(yuv.x, col1.x, col2.x), ditherBlockUV));
	yuv.y = mix(col1.y, col2.y, ditheredChannel(channelError(yuv.y, col1.y, col2.y), ditherBlockUV));
	yuv.z = mix(col1.z, col2.z, ditheredChannel(channelError(yuv.z, col1.z, col2.z), ditherBlockUV));
	
	return(YUVtoRGB(yuv));
}

float3 getPixel(float2 uv)
{
	return tex2D(postTex, uv).rgb;
}

// Sigma 1. Size 3
float3 gaussian(in float2 uv)
{
    float b = blur / (vecViewPort.x / vecViewPort.y);

    uv += 0.5;

    float3 col = tex2D(postTex, float2(uv.x - b / vecViewPort.x, uv.y - b/vecViewPort.y)).rgb * 0.077847;
    col += tex2D(postTex, float2(uv.x - b / vecViewPort.x, uv.y)).rgb * 0.123317;
    col += tex2D(postTex, float2(uv.x - b / vecViewPort.x, uv.y + b / vecViewPort.y)).rgb * 0.077847;

    col += tex2D(postTex, float2(uv.x, uv.y - b / vecViewPort.y)).rgb * 0.123317;
    col += tex2D(postTex, float2(uv.x, uv.y)).rgb * 0.195346;
    col += tex2D(postTex, float2(uv.x, uv.y + b / vecViewPort.y)).rgb * 0.123317;

    col += tex2D(postTex, float2(uv.x + b / vecViewPort.x, uv.y - b / vecViewPort.y)).rgb * 0.077847;
    col += tex2D(postTex, float2(uv.x + b / vecViewPort.x, uv.y)).rgb * 0.123317;
    col += tex2D(postTex, float2(uv.x + b / vecViewPort.x, uv.y + b / vecViewPort.y)).rgb * 0.077847;

    return col;
}

float3 postEffects(in float3 rgb, in float2 xy)
{
	float temp_dot = dot(float3(0.2125, 0.7154, 0.0721), rgb * brightness);
    rgb = pow(rgb, float3(gamma, gamma, gamma));
    rgb = lerp(float3(0.5, 0.5, 0.5), lerp(float3(temp_dot, temp_dot, temp_dot), rgb * brightness, saturation), contrast);

    return rgb;
}

float vignette(float2 uv)
{
	uv = (uv - 0.5) * 0.98;
	return clamp(pow(cos(uv.x * 3.1415), 1.2) * pow(cos(uv.y * 3.1415), 1.2) * 50.0, 0.0, 1.0);
}

float4 FP(float2 fragCoord: VPOS) : COLOR
{
	float2 st = (fragCoord.xy / vecViewPort.xy) - float2(0.5, 0.5);
	float2 vignette_uv = fragCoord / vecViewPort.xy;
	
	// Curvature
    float d = length(st * 0.5 * st * 0.5);
#ifdef CURVATURE
    float2 uv = st * d + st * 0.935;
#else
    float2 uv = st;
#endif
	
	// CRT color blur
#ifdef BLURED
    float3 color = gaussian(uv);
#else
    float3 color = tex2D(postTex, uv + 0.5).rgb;
#endif

	color = ditherColor(color, uv, vecViewPort.x, vecViewPort.y);

    // Light
#ifdef LIGHT
    float l = 1.0 - min(1.0, d * light);
    color *= l;
#endif

#ifdef CURVED_SCANLINES
    float y = uv.y;
#else
    float y = st.y;
#endif
	
	float showScanlines = 1.0;
    if (vecViewPort.y < 360)
	{
		showScanlines = 0.0;
	}
    
    // Scanlines
#ifdef SCANLINES
    float s = 1.0 - smoothstep(320.0, 1440.0, vecViewPort.y) + 1.0;
    float j = cos(y * vecViewPort.y * s) * 0.1; // values between .01 to .25 are ok.
    color = abs(showScanlines - 1.0) * color + showScanlines * (color - color * j);
    color *= 1.0 - (0.01 + ceil(fmod((st.x + 0.5) * vecViewPort.x, 3.0)) * (0.995 - 1.01)) * showScanlines;
#endif

    // Color correction
#ifdef COLOR_CORRECTION
    color = postEffects(color, st);
#endif

	float4 fragColor = float4(max(float3(0, 0, 0), min(float3(1, 1, 1), color)), 1);

#ifdef VIGNETTE
	fragColor *= vignette(vignette_uv);
#endif

	return fragColor;
}

technique psx
{
	pass one
	{
		PixelShader = compile ps_3_0 FP();
	}
}