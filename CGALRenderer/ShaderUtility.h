#ifndef SHADER_UTILITY_H
#define SHADER_UTILITY_H

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

#define VERTEX_SHADER_USE_NORMAL	"#define USE_NORMAL\n"
#define VERTEX_SHADER_USE_COLOR		"#define USE_COLOR\n"
#define VERTEX_SHADER_USE_TEXCOORD	"#define USE_TEXCOORD\n"


#endif SHADER_UTILITY_H
