#ifndef GRAYSCALE_SHADERL_H
#define GRAYSCALE_SHADERL_H

namespace KI
{
namespace Renderer
{
class DLL_EXPORT GrayScaleUniform : public IUniform
{
public:
	SHADER_TYPE Type() { return SHADER_TYPE::SHADER_TYPE_GRAYSCALE; }

	void SetTexture(shared_ptr<Texture> pTexture) { m_pTexture = pTexture; }
	shared_ptr<Texture> GetTexture() { return m_pTexture; }
private:
	shared_ptr<Texture> m_pTexture;
};

class DLL_EXPORT GrayScaleShader : public IShader
{
	enum GRAYSCALE_UNIFORM : unsigned short
	{
		GRAYSCALE_UNIFORM_SOURCE_TEXTURE,
		GRAYSCALE_UNIFORM_NUM
	};

public:

	GrayScaleShader();
	~GrayScaleShader();

	virtual SHADER_TYPE Type() { return SHADER_TYPE::SHADER_TYPE_GRAYSCALE; }

	virtual void Initialize() override;
	virtual void FetchUniformLocation() override;

	virtual void Bind(shared_ptr<UniformSet> pUniform) override;
	virtual void UnBind(shared_ptr<UniformSet> pUniform) override;

private:
	void BindColorTexture();
	shared_ptr<Texture> m_pSource;
};
}
}


#endif GRAYSCALE_SHADERL_H
