#ifndef ISHADER_H
#define ISHADER_H
namespace KI
{
enum SHADER_TYPE
{
	SHADER_TYPE_DEFAULT = 1,
};


struct ShaderBuildInfo
{
	SHADER_TYPE shaderType;
	std::string vertexDefine;
	std::string fragDefine;
};

#define GLSL_VERSION_400_CORE "#version 400 core\n"
#define SHADER_DEBUG

class IShader
{
public:
	void Build(const ShaderBuildInfo& buildInfo);
	void BuildFromCode(const std::string& vertexShaderCode, const std::string& fragmentShader);

	void Use();
	void UnUse();
	void Dispose();

	virtual SHADER_TYPE Type() = 0;
	
	virtual void Initialize() = 0;
	GLuint Program() { return m_programId; }
	bool Compare(const ShaderBuildInfo& buildInfo);

	
protected:
	
	void SetVersion(std::string version) { m_version = version; }
	void SetVertexPath(std::string filePath) { m_vertexPath = filePath; }
	void SetFragPath(std::string filePath) { m_fragPath = filePath; }
	std::string m_version;
	std::string m_vertexPath;
	std::string m_fragPath;
	GLuint m_programId;
	SHADER_TYPE m_shaderType;
private:
	ShaderBuildInfo m_buildInfo;

#ifdef SHADER_DEBUG
	string debug_vertexShader;
	string debug_fragShader;
#endif // SHADER_DEBUG
};
}
#endif ISHADER_H
