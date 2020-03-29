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
	void BuildFromCode(const string& vertexShaderCode, const string& fragmentShader);
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
	bool Compare(IShaderBuildInfo* shaderDefine);
	IShaderBuildInfo* BuildInfo() { return m_pShaderBuildInfo.get(); }
protected:
	virtual void BindTexture(GLint activeNumber, GLint uniformId);
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
