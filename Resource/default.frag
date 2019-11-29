
out vec4 outputColor;

#ifdef USE_TEXCOORD
	in vec2 v_texcoord;
#else
	in vec4 v_color;
#endif


#ifdef USE_TEXTURE0
	//uniform sampler2D uTexcoord0;
#endif

void main()
{
#ifdef USE_TEXTURE0
	outputColor = vec4(1.0,1.0,0.0,1.0);//texture2D(uTexcoord0,v_texcoord);
#else
	outputColor = v_color;//vec4(0.5,0.5,0.5,1.0);
#endif
}