
out vec4 outputColor;

#ifdef USE_TEXCOORD
	in vec2 v_texcoord;
#else
	in vec4 v_color;
#endif


#ifdef USE_TEXTURE0
uniform sampler2D uTexture0;
#endif

void main()
{
#ifdef USE_TEXTURE0
	outputColor = texture2D(uTexture0,v_texcoord);
#else
	outputColor = v_color;
#endif
}