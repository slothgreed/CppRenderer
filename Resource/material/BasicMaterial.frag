#include "common/common.h"

#ifdef VIEW_TEXTURE
	uniform sampler2D uTexture0;
#endif

#if def VIEW_FIXCOLOR
uniform vec4 uFixColor;
#endif

void OutputColorExt()
{
#if defined(VIEW_TEXTURE)
	outputColor = texture2D(uTexture0,InData.texcoord);
#elif defined(VIEW_FIXCOLOR)
	outputColor = uFixColor;
#elif
	outputColor = NotDefinedColor();
#endif
}