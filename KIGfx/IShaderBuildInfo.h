#ifndef ISHADER_BUILD_INFO_H
#define	ISHADER_BUILD_INFO_H
namespace KI
{
namespace Gfx
{
class DLL_EXPORT IShaderBuildInfo
{
public:
	IShaderBuildInfo() { assert(0); }
	IShaderBuildInfo(SHADER_TYPE type);
	~IShaderBuildInfo();

	SHADER_TYPE Type() { return m_type; };
	void AddEmbeddedCode(shared_ptr<IEmbeddedShaderCode> value) { m_pEmbeddedCode.push_back(value); }
	shared_ptr<IEmbeddedShaderCode> GetEmbeddedCode(int index) { return m_pEmbeddedCode[index]; };
	const vector<shared_ptr<IEmbeddedShaderCode>> GetEmbeddedCode() { return m_pEmbeddedCode; };
	int GetEmbeddedCodeSize() { return (int)m_pEmbeddedCode.size(); };
	void SetVertexCode(shared_ptr<IShaderCode> value) { m_pShaderCode[SHADER_PROGRAM_VERTEX] = value; };
	void SetTESCode(shared_ptr<IShaderCode> value) { m_pShaderCode[SHADER_PROGRAM_TESS] = value; };
	void SetTCSCode(shared_ptr<IShaderCode> value) { m_pShaderCode[SHADER_PROGRAM_TCS] = value; };
	void SetGeomCode(shared_ptr<IShaderCode> value) { m_pShaderCode[SHADER_PROGRAM_GEOM] = value; };
	void SetFragCode(shared_ptr<IShaderCode> value) { m_pShaderCode[SHADER_PROGRAM_FRAG] = value; };

	shared_ptr<IShaderCode> GetShaderCode(SHADER_PROGRAM_TYPE type) { return m_pShaderCode[type]; }
	bool Compare(IShaderBuildInfo* pShaderBuildInfo);
private:
	shared_ptr<IShaderCode> m_pShaderCode[SHADER_PROGRAM_NUM];
	vector<shared_ptr<IEmbeddedShaderCode>> m_pEmbeddedCode;
	
	SHADER_TYPE m_type;
};

}
}
#endif // !IRENDERTARGET_H