#include "common\common.h"
#include "common\struct.h"
out vec4 outputColor;

#ifdef VIEW_TEXTURE
	uniform sampler2D uTexture0;
#endif

#ifdef VIEW_FIXCOLOR
uniform vec4 uFixColor;
#endif

#if defined(VIEW_TEXTURE)
in Data{
	in vec2 texcoord;
}InData;
#endif


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