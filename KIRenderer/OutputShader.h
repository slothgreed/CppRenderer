#ifndef OUTPUT_SHADER_H
#define OUTPUT_SHADER_H

namespace KI
{
namespace Renderer
{

class DLL_EXPORT OutputUniform : public IUniform
{
public:
	virtual SHADER_TYPE Type() override { return SHADER_TYPE::SHADER_TYPE_OUTPUT; }
public:
	void SetTexture(shared_ptr<Texture> pTexture) { m_pTexture = pTexture; }
	shared_ptr<Texture> GetTexture() { return m_pTexture; }
private:
	shared_ptr<Texture> m_pTexture;
};


class DLL_EXPORT OutputShader : public IShader
{
	enum OUTPUT_UNIFORM : unsigned short
	{
		OUTPUT_UNIFORM_COLOR_TEXTURE,
		OUTPUT_UNIFORM_NUM
	};
public:
	OutputShader();
	~OutputShader();
	virtual SHADER_TYPE Type() override { return SHADER_TYPE::SHADER_TYPE_OUTPUT; }
	virtual void Initialize() override;
	virtual void FetchUniformLocation() override;
	virtual void Bind(shared_ptr<UniformSet> pUniform) override;
	virtual void UnBind(shared_ptr<UniformSet> pUniform) override;
private:
	void BindOutputTexture();
	shared_ptr<UniformSet> m_pUniform;
};
}
}


#endif OUTPUT_SHADER_H