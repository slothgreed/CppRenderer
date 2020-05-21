#ifndef SSLIC_SHADER_H
#define SSLIC_SHADER_H

namespace KI
{
namespace Renderer
{

class DLL_EXPORT SSLICMaterial : public IMaterial
{
public:
	virtual shared_ptr<IShaderCode> NewShaderCode(IShaderBuildInfo* pBuildInfo,SHADER_PROGRAM_TYPE type);

	void SetTexture(shared_ptr<Texture> value) { m_pTexture = value; };
	shared_ptr<Texture> GetTexture() { return m_pTexture; };

private:
	shared_ptr<Texture> m_pTexture;
};


class DLL_EXPORT SSLICFragCode : public IShaderCode
{
public:
	enum SSLIC_UNIFORM : unsigned short
	{
		SSLIC_UNIFORM_COLOR_TEXTURE,
		SSLIC_UNIFORM_NUM
	};

	SSLICFragCode();
	~SSLICFragCode();

	virtual void Initialize(GLuint programId) override;
	virtual bool Compare(IShaderCode* pShaderCode) override { return true; };
	virtual void Bind(shared_ptr<IShaderChunk> pShaderChunk) override;
	virtual void UnBind(shared_ptr<IShaderChunk> pShaderChunk) override;

private:
};
}
}

#endif SSLIC_SHADER_H