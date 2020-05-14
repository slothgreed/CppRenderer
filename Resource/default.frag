
out vec4 outputColor;

in Data{
#ifdef IN_NORMAL
	in vec4 normal;
#endif
	in vec4 color;
#ifdef IN_TEXCOORD
	in vec2 texcoord;
#endif
}InData;

<<<Embedded Code Area>>>

void main()
{
#if defined(OUTPUT_COLOR_EXT)
	OutputColorExt();
#elif
	outputColor = InData.color;
#endif
}




