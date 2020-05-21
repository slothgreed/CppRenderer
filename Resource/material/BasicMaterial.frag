#include "common\common.h"

out vec4 outputColor;

#ifdef VIEW_TEXTURE
	uniform sampler2D uTexture0;
#endif

#ifdef VIEW_FIXCOLOR
uniform vec4 uFixColor;
#endif

in Data{
#if defined(VIEW_FIXCOLOR)
	in vec4 color;
#elif defined(VIEW_TEXTURE)
	in vec2 texcoord;
#else
	in vec4 color;
#endif
}InData;


void main()
{
#if defined(VIEW_TEXTURE)
	outputColor = texture2D(uTexture0,InData.texcoord);
#elif defined(VIEW_FIXCOLOR)
	outputColor = uFixColor;
#else
	outputColor = NotDefinedColor();
#endif
}