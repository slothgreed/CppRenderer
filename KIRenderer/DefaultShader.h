#ifndef DEFAULT_SHADER_H
#define DEFAULT_SHADER_H

namespace KI
{
namespace Renderer
{
class DLL_EXPORT DefaultShader : public IShader
{
	enum UNIFORM_LOCATION : unsigned short
	{
		DEFAULT_UNIFORM_COLOR_TEXTURE,
		DEFAULT_UNIFORM_FIX_COLOR,
		DEFAULT_UNIFORM_NUM
	};
public:
	DefaultShader();
	~DefaultShader();

	virtual SHADER_TYPE Type() override { return SHADER_TYPE::SHADER_TYPE_DEFAULT; }

	virtual void Initialize() override;
	virtual void FetchUniformLocation() override;
	virtual void Bind(shared_ptr<UniformSet> pUniform) override;
	virtual void UnBind(shared_ptr<UniformSet> pUniform) override;
	
private:
	void BindColorTexture();
	void BindFixColor(const vec4& color);
	void BindScene();
	void BindLight();
};

class DLL_EXPORT DefaultVertexUniform : public IUniform
{
public:
	DefaultVertexUniform() :  m_FixColor(vec4(0.7f, 0.7f, 0.7f, 1)), m_visible(false) {}
	SHADER_TYPE Type() { return SHADER_TYPE::SHADER_TYPE_DEFAULT; }

	bool VisibleNormal() { return m_visible; }
	void VisibleNormal(bool value) { m_visible = value; }
	void SetFixColor(const vec4& value) { m_FixColor = value; };
	const vec4&		FixColor() { return m_FixColor; }
private:
	vec4 m_FixColor;
	bool m_visible;
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