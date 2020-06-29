#ifndef COMPOSIT_SHADERL_H
#define COMPOSIT_SHADERL_H

namespace KI
{
namespace Renderer
{
enum COMPOSIT_TYPE
{
	COMPOSIT_TYPE_ADD,
	COMPOSIT_TYPE_SUB,
	COMPOSIT_TYPE_MULT,
	COMPOSIT_TYPE_OVERWRITE,
	COMPOSIT_TYPE_NUM
};

class DLL_EXPORT CompositFragCode : public IShaderCode
{
public:

	enum COMPOSIT_UNIFORM : unsigned short
	{
		COMPOSIT_UNIFORM_SOURCE_TEXTURE,
		COMPOSIT_UNIFORM_TARGET_TEXTURE,
		COMPOSIT_UNIFORM_NUM
	};

	CompositFragCode(COMPOSIT_TYPE type);
	~CompositFragCode();

	virtual void GetDefineCode(string& code) override;
	virtual bool Compare(IShaderCode* pShaderCode) override;

	virtual void Initialize(GLuint programId) override;
	virtual void Bind(shared_ptr<IShaderChunk> pShaderChunk) override;
	virtual void UnBind(shared_ptr<IShaderChunk> pShaderChunk) override;

private:
	COMPOSIT_TYPE m_CompositType;
};

class DLL_EXPORT CompositShading : public IShading
{
public:
	CompositShading(COMPOSIT_TYPE type) { m_Type = type; }
	shared_ptr<Texture> GetSource() { return m_pSource; }
	shared_ptr<Texture> GetDestination() { return m_pDestination; }
	virtual shared_ptr<IShaderCode> NewShaderCode(IShaderBuildInfo* pBuildInfo,SHADER_PROGRAM_TYPE type) = 0;
private:
	shared_ptr<Texture> m_pSource;
	shared_ptr<Texture> m_pDestination;
	COMPOSIT_TYPE m_Type;

};

}
}
#endif COMPOSIT_SHADERL_H
