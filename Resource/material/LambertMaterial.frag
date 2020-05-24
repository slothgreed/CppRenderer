#include "common\common.h"

out vec4 outputColor;

#ifdef IN_TEXTURE
uniform sampler2D uTexture0;
in Data{
	in vec3 normal;
	in vec2 texcoord;
}InData;
#endif

#ifdef IN_COLOR
in Data{
	in vec3 normal;
	in vec4 color;
}InData;
#endif

#ifdef IN_FIXCOLOR
uniform vec4 uFixColor;
#endif

vec4 GetColor()
{
#if defined(IN_TEXTURE)
	return texture2D(uTexture0,InData.texcoord);
#elif defined(IN_COLOR)
	return InData.color;
#elif defined(IN_FIXCOLOR)
	return uFixColor;
#endif
}

vec4 Lambert()
{
	vec3 direction = light.Direction;
	float diffuse = clamp(dot(InData.normal,direction),0.1);
	return diffuse * GetColor();
}

void main()
{
	outputColor = Lambert();
}