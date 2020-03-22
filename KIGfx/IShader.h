#ifndef ISHADER_H
#define ISHADER_H
namespace KI
{
namespace Gfx
{
#define GLSL_VERSION_400_CORE "#version 400 core\n"
#define SHADER_DEBUG


class DLL_EXPORT IShader
{
public:
	void Build(shared_ptr<IShaderDefine> pShaderDefine);
	void GenerateShaderCode(IShaderDefine* pShaderDefine);
	void BuildFromCode(const std::string& vertexShaderCode, const std::string& fragmentShader);
	void GetShaderCode(SHADER_PROGRAM_TYPE type, string& code);
	void Use();
	void UnUse();
	void Dispose();

	virtual SHADER_TYPE Type() = 0;
	
	virtual void Initialize() = 0;
	virtual void FetchUniformLocation() = 0;
	virtual void Bind(shared_ptr<IUniform> uniform) = 0;
	virtual void UnBind() = 0;
	GLuint Program() { return m_programId; }
	bool Compare(IShaderDefine* shaderDefine);
	IShaderDefine* GetShaderDefine() { return m_pShaderDefine.get(); }
	
protected:
	virtual void BindTexture(GLint activeNumber, GLint uniformId);
	virtual void BindVector4(GLint uniformId, vec4 value);

	void SetVersion(string version) { m_version = version; }
	void SetVertexPath(string filePath) { m_shaderPath[SHADER_PROGRAM_VERTEX] = filePath; }
	void SetGeomPath(string filePath) { m_shaderPath[SHADER_PROGRAM_GEOM] = filePath; }
	void SetFragPath(string filePath) { m_shaderPath[SHADER_PROGRAM_FRAG] = filePath; }
	GLuint m_programId;
	SHADER_TYPE m_shaderType;
	vector<GLint> m_uniformLocation;
private:
	bool UniformValidation();
	shared_ptr<IShaderDefine> m_pShaderDefine;
	string m_version;
	string m_vertexPath;
	string m_geomPath;
	string m_fragPath;
	string m_shaderPath[SHADER_PROGRAM_NUM];
#ifdef SHADER_DEBUG
	string debug_vertexShader;
	string debug_geomShader;
	string debug_fragShader;
#endif // SHADER_DEBUG
};
}
}
#endif ISHADER_H
