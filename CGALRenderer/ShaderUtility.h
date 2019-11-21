#ifndef SHADER_UTILITY_H
#define SHADER_UTILITY_H
namespace KI
{
class ShaderUtility
{
public:
	ShaderUtility();
	~ShaderUtility();
	

	static GLuint Compile(const std::string& code, GLuint shaderType);
	static GLuint Link(GLuint vertexId, GLuint fragId);
	
	static void SetShaderDirectory(std::string directoryPath) { m_shaderDirectory = directoryPath; }
	static const std::string& ShaderDirectory();
private:

	static std::string m_shaderDirectory;

};

}

#endif SHADER_UTILITY_H
