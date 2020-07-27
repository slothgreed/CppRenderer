#ifndef GL_STRUCT_H
#define	GL_STRUCT_H
namespace KI
{
namespace Gfx
{
struct DLL_EXPORT ReadPixelArgs
{
	~ReadPixelArgs();
	int x;
	int y;
	int width;
	int height;
	GLuint format;
	GLuint type;
	void* pixels;
};
}
}
#endif // !GL_WRAPPER_H
