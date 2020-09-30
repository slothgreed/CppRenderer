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

void glEx::GetDebugInfoSourceStr(GLenum source, string* str)
{
	static const char* sourceStr[] = {
		"OpenGL API",
		"Window System",
		"Shader Compiler",
		"Third Party",
		"Application",
		"Other",
	};
	int sourceNo = (GL_DEBUG_SOURCE_API_ARB <= source && source <= GL_DEBUG_SOURCE_OTHER_ARB)
		? (source - GL_DEBUG_SOURCE_API_ARB)
		: (GL_DEBUG_SOURCE_OTHER_ARB - GL_DEBUG_SOURCE_API_ARB);

	*str = sourceStr[sourceNo];
}

void glEx::GetDebugInfoTypeStr(GLenum type, string* str)
{
	static const char* typeStr[] = {
		"Error",
		"Deprecated behavior",
		"Undefined behavior",
		"Portability",
		"Performance",
		"Other",
	};

	int typeNo = (GL_DEBUG_TYPE_ERROR_ARB <= type && type <= GL_DEBUG_TYPE_OTHER_ARB)
		? (type - GL_DEBUG_TYPE_ERROR_ARB)
		: (GL_DEBUG_TYPE_OTHER_ARB - GL_DEBUG_TYPE_ERROR_ARB);

	*str = typeStr[typeNo];
}

void glEx::GetDebugInfoSeverityStr(GLenum severity, string* str)
{
	static const char* severityStr[] = {
	"High",
	"Medium",
	"Low",
	};
	int severityNo = (GL_DEBUG_SEVERITY_HIGH_ARB <= severity && severity <= GL_DEBUG_SEVERITY_LOW_ARB)
		? (severity - GL_DEBUG_SEVERITY_HIGH_ARB)
		: (GL_DEBUG_SEVERITY_LOW_ARB - GL_DEBUG_SEVERITY_HIGH_ARB);

	*str = severityStr[severityNo];
}

}
}