#ifndef GL_TYPE_UTILITY_H
#define GL_TYPE_UTILITY_H
namespace KI
{
namespace Gfx
{
class DLL_EXPORT GLTypeUtility
{
public:
	GLTypeUtility() {};
	~GLTypeUtility() {};
	
	static PRIM_TYPE PrimType(GLuint value);

private:

};
}
}

#endif GL_TYPE_UTILITY_H
