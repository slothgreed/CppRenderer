namespace KI
{
namespace Gfx
{

int glEx::ColorFormatSize(GLuint formatSize)
{
	if (formatSize == GL_COLOR_INDEX ||
		formatSize == GL_STENCIL_INDEX ||
		formatSize == GL_DEPTH_COMPONENT ||
		formatSize == GL_RED ||
		formatSize == GL_GREEN ||
		formatSize == GL_BLUE ||
		formatSize == GL_ALPHA ||
		formatSize == GL_LUMINANCE_ALPHA)
	{
		return 1;
	}else if (
		formatSize == GL_RGB ||
		formatSize == GL_BGR ||
		formatSize == GL_LUMINANCE)
	{
		return 3;
	} else if (
		formatSize == GL_RGBA ||
		formatSize == GL_BGRA)
	{
		return 4;
	}
	else
	{
		assert(0);
	}

	return 1;
}
}
}