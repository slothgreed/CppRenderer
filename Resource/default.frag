
out vec4 outputColor;


#ifdef USE_TEXTURE0
	uniform sampler2D uTexture0;
	in vec2 v_texcoord;
#else
	in vec4 v_color;
#endif

#ifdef USE_NORMAL
in vec4 v_normal;
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
in vec4 v_position;
#endif

void OutputGBuffer()
{
#if defined(USE_GBUFFER)
#if defined(USE_NORMAL) && defined(USE_TEXTURE0)
	vec4 position = v_position / v_position.w;
	OutputColor0 = (position + 1) * 0.5;
	OutputColor1 = vec4((normalize(v_normal)+1.0)*0.5,1);
	OutputColor2 = vec4(uTexture0, v_texcoord);
	OutputColor3 = vec4(1);
#elif defined(USE_NORMAL)
	vec4 position = v_position / v_position.w;
	OutputColor0 = (position + 1) * 0.5;
	OutputColor1 = vec4((normalize(v_normal)+1.0)*0.5,1);
	OutputColor2 = v_color;
	OutputColor3 = vec4(1);
#elif defined(USE_TEXTURE0)
	vec4 position = v_position / v_position.w;
	OutputColor0 = (position + 1) * 0.5;
	OutputColor1 = vec4(1);
	OutputColor2 = vec4(uTexture0, v_texcoord);
	OutputColor3 = vec4(1);
#endif
#endif
}

vec4 Shading()
{
#if defined(USE_SHADING)
#if defined(USE_TEXTURE0)
	return texture2D(uTexture0,v_texcoord);
#elif defined (USE_NORMAL)
	return dot(normalize(light.Direction),v_color) * vec4(1.0);
#else
	return v_color * vec4(0,0.7,0.7,1.0);
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
#elif defined(USE_TEXTURE0)
	outputColor = texture2D(uTexture0,v_texcoord);
#else
	outputColor = vec4(v_color.xyz,1.0);
#endif
}