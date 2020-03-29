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
	void SetVertexCode(shared_ptr<IShaderCode> value) { m_pShaderCode[SHADER_PROGRAM_VERTEX] = value; };
	void SetGeomCode(shared_ptr<IShaderCode> value) { m_pShaderCode[SHADER_PROGRAM_GEOM] = value; };
	void SetFragCode(shared_ptr<IShaderCode> value) { m_pShaderCode[SHADER_PROGRAM_FRAG] = value; };

	IShaderCode* GetShaderCode(SHADER_PROGRAM_TYPE type) { return m_pShaderCode[type].get(); }

	bool Compare(IShaderBuildInfo* pShaderBuildInfo);
private:
	shared_ptr<IShaderCode> m_pShaderCode[SHADER_PROGRAM_NUM];
	
	SHADER_TYPE m_type;
};

}
}
#endif // !IRENDERTARGET_H