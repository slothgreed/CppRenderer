
out vec4 outputColor;

#ifdef IN_TEXTURE0
	uniform sampler2D uTexture0;
#endif

#ifdef IN_TEXCOORD
	in vec2 o_texcoord;
#endif

in vec4 o_color;

#ifdef IN_NORMAL
in vec4 o_normal;
#endif


layout (std140) uniform LightData
{
	vec4 Direction;
	vec4 Ambient;
	vec4 Diffuse;
	vec4 Specular;
}light;

#ifdef USE_GBUFFER
out vec4 OutputColor0;
out vec4 OutputColor1;
out vec4 OutputColor2;
out vec4 OutputColor3;
in vec4 o_position;
#endif

void OutputGBuffer()
{
#if defined(USE_GBUFFER)
#if defined(IN_NORMAL) && defined(IN_TEXCOORD)
	vec4 position = o_position / o_position.w;
	OutputColor0 = (position + 1) * 0.5;
	OutputColor1 = vec4((normalize(o_normal)+1.0)*0.5,1);
	OutputColor2 = vec4(uTexture0, o_texcoord);
	OutputColor3 = vec4(1);
#elif defined(IN_NORMAL)
	vec4 position = o_position / o_position.w;
	OutputColor0 = (position + 1) * 0.5;
	OutputColor1 = vec4((normalize(o_normal)+1.0)*0.5,1);
	OutputColor2 = o_color;
	OutputColor3 = vec4(1);
#elif defined(IN_TEXCOORD)
	vec4 position = o_position / o_position.w;
	OutputColor0 = (position + 1) * 0.5;
	OutputColor1 = vec4(1);
	OutputColor2 = vec4(uTexture0, o_texcoord);
	OutputColor3 = vec4(1);
#endif
#endif
}

vec4 Shading()
{
#if defined(USE_SHADING)
#if defined(IN_TEXTURE0)
	return texture2D(uTexture0,o_texcoord);
#elif defined (USE_NORMAL)
	return dot(normalize(light.Direction),o_color) * vec4(1.0);
#else
	return o_color * vec4(0,0.7,0.7,1.0);
#endif
#endif
	return vec4(1,1,0,1);
}

void main()
{
#if defined(USE_GBUFFER)
	OutputGBuffer()
#elif defined(USE_SHADING)
	outputColor = Shading();
#elif defined(IN_TEXTURE0)
	outputColor = texture2D(uTexture0,o_texcoord);
#else
	outputColor = vec4(o_color.xyz,1.0);
#endif
}