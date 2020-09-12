#ifndef GRAYSCALE_SHADERL_H
#define GRAYSCALE_SHADERL_H

namespace KI
{
namespace ShaderLib
{
class DLL_EXPORT GrayScaleShading : public IShading
{
public:
	SHADER_TYPE Type() { return SHADER_TYPE::SHADER_TYPE_GRAYSCALE; }

	void SetTexture(shared_ptr<Texture> pTexture) { m_pTexture = pTexture; }
	shared_ptr<Texture> GetTexture() { return m_pTexture; }

	virtual bool NewShaderCompare(IShaderChunk* pTarget) override;
	virtual shared_ptr<IShaderCode> NewShaderCode(IShaderBuildInfo* pBuildInfo,SHADER_PROGRAM_TYPE type) override;


private:
	shared_ptr<Texture> m_pTexture;
};

class DLL_EXPORT GrayScaleFragCode : public IShaderCode
{
	enum GRAYSCALE_UNIFORM : unsigned short
	{
		GRAYSCALE_UNIFORM_SOURCE_TEXTURE,
		GRAYSCALE_UNIFORM_NUM
	};

public:

	GrayScaleFragCode();
	~GrayScaleFragCode();

	virtual SHADER_TYPE Type() { return SHADER_TYPE::SHADER_TYPE_GRAYSCALE; }

	virtual void Initialize(GLuint programId) override;
	void FetchUniformLocation(GLuint programId);

	virtual bool Compare(IShaderCode* pShaderCode) override { return true; };
	virtual void Bind(shared_ptr<IShaderChunk> pShaderChunk,shared_ptr<IUniformStorage> pUniform) override;
	virtual void UnBind(shared_ptr<IShaderChunk> pShaderChunk,shared_ptr<IUniformStorage> pUniform) override;

private:
	void BindColorTexture();
	shared_ptr<Texture> m_pSource;
};
}
}


#endif GRAYSCALE_SHADERL_H
