#ifndef SHADER_H
#define SHADER_H

class Shader
{
public:
	Shader();
	~Shader();

	void BuildFromFile(const std::string& versionPath, const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
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