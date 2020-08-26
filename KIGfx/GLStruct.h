#ifndef GL_STRUCT_H
#define	GL_STRUCT_H
namespace KI
{
namespace Gfx
{
struct DLL_EXPORT ReadPixelArgs
{
	ReadPixelArgs(): x(0), y(0), width(1), height(1), format(0), type(0) {}
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
