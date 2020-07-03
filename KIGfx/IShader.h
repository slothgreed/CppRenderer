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
	void Initialize();
	void Use();
	void UnUse();
	void Dispose();
	void Bind(shared_ptr<IShaderChunk> pShaderChunk,shared_ptr<IUniformStorage> pUniform);
	void UnBind(shared_ptr<IShaderChunk> pShaderChunk,shared_ptr<IUniformStorage> pUniform);

	void AddIncludeCode(shared_ptr<IShaderCode> pShaderCode) { m_pIncludeCode.push_back(pShaderCode); };
	
	GLuint Program() { return m_programId; }
	bool Compare(IShaderBuildInfo* shaderDefine);
	shared_ptr<IShaderBuildInfo> BuildInfo() { return m_pShaderBuildInfo; }


	GLuint m_programId;
private:
	void GenerateShaderCode(IShaderBuildInfo* pShaderBuildInfo);
	

	shared_ptr<IShaderCode> m_pShaderCodes[SHADER_PROGRAM_NUM];
	vector<shared_ptr<IShaderCode>> m_pIncludeCode;
	string m_version;

	string debug_vertexCode;
	string debug_tcsCode;
	string debug_tesCode;
	string debug_geomCode;
	string debug_fragCode;

	shared_ptr<IShaderBuildInfo> m_pShaderBuildInfo;
};
}
}
#endif ISHADER_H
