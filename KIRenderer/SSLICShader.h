#ifndef SSLIC_SHADER_H
#define SSLIC_SHADER_H

namespace KI
{
namespace Renderer
{

class DLL_EXPORT SSLICUniform : public IUniform
{
public:
	virtual SHADER_TYPE Type() override { return SHADER_TYPE::SHADER_TYPE_SSLIC; }
	void SetTexture(shared_ptr<Texture> value) { m_pTexture = value; };
	shared_ptr<Texture> GetTexture() { return m_pTexture; };

private:
	shared_ptr<Texture> m_pTexture;
};


class DLL_EXPORT SSLICShader : public IShader
{
public:
	enum SSLIC_UNIFORM : unsigned short
	{
		SSLIC_UNIFORM_COLOR_TEXTURE,
		SSLIC_UNIFORM_NUM
	};

	SSLICShader();
	~SSLICShader();

	virtual SHADER_TYPE Type() override { return SHADER_TYPE::SHADER_TYPE_SSLIC; }
	virtual void Initialize() override;
	virtual void FetchUniformLocation() override;
	virtual void Bind(shared_ptr<IMaterial> pMaterial, shared_ptr<UniformSet> pUniform) override;
	virtual void UnBind(shared_ptr<IMaterial> pMaterial, shared_ptr<UniformSet> pUniform) override;

private:
	void BindColorTexture();
};
}
}

#endif SSLIC_SHADER_H