#ifndef ISHADER_H
#define ISHADER_H
namespace KI
{


#define GLSL_VERSION_400_CORE "#version 400 core\n"
#define SHADER_DEBUG


class IShader
{
public:
	void Build(shared_ptr<IShaderDefine> shaderDefine);
	void BuildFromCode(const std::string& vertexShaderCode, const std::string& fragmentShader);

	void Use();
	void UnUse();
	void Dispose();

	virtual SHADER_TYPE Type() = 0;
	
	virtual void Initialize() = 0;
	virtual void FetchUniformLocation() = 0;
	virtual void Bind(shared_ptr<IUniform> uniform) = 0;
	virtual void UnBind() = 0;
	GLuint Program() { return m_programId; }
	bool Compare(shared_ptr<IShaderDefine> shaderDefine);

	
protected:
	virtual void BindTexture(GLint activeNumber, GLint uniformId);
	void SetVersion(std::string version) { m_version = version; }
	void SetVertexPath(std::string filePath) { m_vertexPath = filePath; }
	void SetFragPath(std::string filePath) { m_fragPath = filePath; }
	std::string m_version;
	std::string m_vertexPath;
	std::string m_fragPath;
	GLuint m_programId;
	SHADER_TYPE m_shaderType;
	vector<GLint> m_uniformLocation;
private:
	bool UniformValidation();
	shared_ptr<IShaderDefine> m_shaderDefine;

#ifdef SHADER_DEBUG
	string debug_vertexShader;
	string debug_fragShader;
#endif // SHADER_DEBUG
};
}
#endif ISHADER_H
