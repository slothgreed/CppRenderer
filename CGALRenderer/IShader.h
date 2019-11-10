#ifndef ISHADER_H
#define ISHADER_H

struct ShaderBuildInfo
{
	std::string vertexDefine;
	std::string fragDefine;
};


enum SHADER_TYPE
{
	SHADER_TYPE_DEFAULT = 1,
};

class IShader
{
public:
	void Build(const ShaderBuildInfo& buildInfo);
	void BuildFromCode(const std::string& vertexShaderCode, const std::string& fragmentShader);

	void Use();
	void UnUse();

	virtual SHADER_TYPE Type() = 0;
	
	virtual void Initialize() = 0;
	GLuint Program() { return m_programId; }
	
	
protected:
	
	void SetVersionPath(std::string filePath) { m_versionPath = filePath; }
	void SetVertexPath(std::string filePath) { m_vertexPath = filePath; }
	void SetFragPath(std::string filePath) { m_fragPath = filePath; }

	std::string m_versionPath;
	std::string m_vertexPath;
	std::string m_fragPath;
	GLuint m_programId;
	SHADER_TYPE m_shaderType;
};
#endif ISHADER_H
