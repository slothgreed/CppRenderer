#ifndef SHADER_UTILITY_H
#define SHADER_UTILITY_H
namespace KI
{
namespace Gfx
{
class DLL_EXPORT ShaderUtility
{
public:
	ShaderUtility();
	~ShaderUtility();
	
	static GLuint Compile(const string& code, GLuint shaderType);
	static GLuint Link(GLuint vertexId, GLuint geomId, GLuint fragId);

private:

	static string m_shaderDirectory;

};
}
}

#endif SHADER_UTILITY_H
