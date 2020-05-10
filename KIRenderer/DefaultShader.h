#ifndef DEFAULT_SHADER_H
#define DEFAULT_SHADER_H

namespace KI
{
namespace Renderer
{
class DLL_EXPORT DefaultShader : public IShader
{

public:
	DefaultShader();
	~DefaultShader();

	virtual SHADER_TYPE Type() override { return SHADER_TYPE::SHADER_TYPE_DEFAULT; }

	virtual void Initialize() override;
	virtual void FetchUniformLocation() override;
	virtual void Bind(shared_ptr<IMaterial> pMaterial, shared_ptr<UniformSet> pUniform) override;
	virtual void UnBind(shared_ptr<IMaterial> pMaterial, shared_ptr<UniformSet> pUniform) override;
	
private:
	void BindScene();
	void BindLight();
};

class DLL_EXPORT DefaultVertexUniform : public IUniform
{
public:
	DefaultVertexUniform() {};
	~DefaultVertexUniform() {};
	SHADER_TYPE Type() { return SHADER_TYPE::SHADER_TYPE_DEFAULT; }

private:

};

class DLL_EXPORT DefaultFragUniform : public IUniform
{
public:
	DefaultFragUniform() : m_pTexture(nullptr) {}
	SHADER_TYPE Type() { return SHADER_TYPE::SHADER_TYPE_DEFAULT; }

	void SetTexture(shared_ptr<Texture> value) { m_pTexture = value; };
	shared_ptr<Texture> GetTexture() { return m_pTexture; }
private:
	shared_ptr<Texture> m_pTexture;
};

}
}
#endif DEFAULT_SHADER_H