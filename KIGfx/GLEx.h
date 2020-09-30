#ifndef GL_EX_H
#define	GL_EX_H
namespace KI
{
namespace Gfx
{
class DLL_EXPORT glEx
{
public:
	glEx() {};
	~glEx() {};

	static int ColorFormatSize(GLuint format);
	static void GetDebugInfoSourceStr(GLenum source, string* str);
	static void GetDebugInfoTypeStr(GLenum type, string* str);
	static void GetDebugInfoSeverityStr(GLenum severity, string* str);
private:

};
}
}

#endif