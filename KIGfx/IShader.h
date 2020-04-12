#ifndef ISHADER_H
#define ISHADER_H
namespace KI
{
namespace Gfx
{
#define SHADER_DEBUG


class DLL_EXPORT IShader
{
public:
	void Build(shared_ptr<IShaderBuildInfo> pShaderBuildInfo);
	void BuildFromCode(const string& vertexCode, const string& tcsCode, const string& tesCode, const string& geomCode, const string& fragShader);
	void GetShaderCode(SHADER_PROGRAM_TYPE type, string& code);
	void Use();
	void UnUse();
	void Dispose();

	virtual SHADER_TYPE Type() = 0;
	
	virtual void Initialize() = 0;
	virtual void FetchUniformLocation() = 0;
	virtual void Bind(shared_ptr<IUniform> pUniform) = 0;
	virtual void UnBind(shared_ptr<IUniform> pUniform) = 0;

	GLuint Program() { return m_programId; }
	bool Compare(IShaderBuildInfo* shaderDefine);
	shared_ptr<IShaderBuildInfo> BuildInfo() { return m_pShaderBuildInfo; }
protected:
	virtual void BindTexture(GLint activeNumber, GLint uniformId);
	virtual void BindInt(GLint uniformId, int value);
	virtual void BindFloat(GLint uniformId, float value);
	virtual void BindVector3(GLint uniformId, vec3 value);
	virtual void BindVector4(GLint uniformId, vec4 value);

	GLuint m_programId;
	vector<GLint> m_uniformLocation;
private:
	void GenerateShaderCode(IShaderBuildInfo* pShaderBuildInfo);
	bool UniformValidation();
	string m_version;
	shared_ptr<IShaderBuildInfo> m_pShaderBuildInfo;
};
}
}
#endif ISHADER_H
