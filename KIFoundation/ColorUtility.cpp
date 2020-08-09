
namespace KI
{
namespace Foundation
{
ColorUtility::ColorUtility()
{
}

ColorUtility::~ColorUtility()
{
}

vec3 ColorUtility::IndexToColor(int index)
{
	vec3 color;
	color.r = (float)((index & 0x000000FF) >> 0) / 255.0f;
	color.g = (float)((index & 0x0000FF00) >> 8) / 255.0f;
	color.b = (float)((index & 0x00FF0000) >> 16) / 255.0f;
	return color;
}
}
}
