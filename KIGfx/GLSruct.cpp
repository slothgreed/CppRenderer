namespace KI
{
namespace Gfx
{

ReadPixelArgs::~ReadPixelArgs()
{
	if (pixels != NULL)
	{
		delete pixels;
		pixels = NULL;
	}
}
}
}