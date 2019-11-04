#ifndef SHADER_H
#define SHADER_H

struct ShaderBuildInfo
{
	std::string versionPath;
	std::string vertexPath;
	std::string vertexDefine;
	std::string fragmentPath;
	std::string fragementDefine;
};

class Shader
{
public:
	Shader();
	~Shader();

	void Build(const ShaderBuildInfo& buildInfo);
	void BuildFromCode(const std::string& vertexShaderCode, const std::string& fragmentShader);
	GLuint Program() { return m_programId; }
	void Use();
	void UnUse();
private:
	GLuint Compile(const std::string& code, GLuint shaderType);
	void Link(GLuint vertexId, GLuint fragId);
	GLuint m_vertexShader;
	GLuint m_fragShader;
	GLuint m_programId;
};

#endif SHADER_H