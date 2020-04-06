#ifndef DEFAULT_SHADER_H
#define DEFAULT_SHADER_H

namespace KI
{
namespace Renderer
{
class DefaultUniform;

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
	virtual void Bind(shared_ptr<IUniform> uniform) override;
	virtual void UnBind() override;
	
private:
	void BindColorTexture();
	void BindFixColor();
	void BindScene();
	void BindLight();
	shared_ptr<DefaultUniform> m_uniformParameter;
};

class DLL_EXPORT DefaultUniform : public IUniform
{
public:
	DefaultUniform() :m_pTexture(nullptr), m_FixColor(vec4(0.7f, 0.7f, 0.7f, 1)) {}
	SHADER_TYPE Type() { return SHADER_TYPE::SHADER_TYPE_DEFAULT; }

	void SetTexture(shared_ptr<Texture> value) { m_pTexture = value; };
	void SetFixColor(vec4 value) { m_FixColor = value; };
	shared_ptr<Texture> GetTexture() { return m_pTexture; }
	const vec4&		FixColor() { return m_FixColor; }
private:
	shared_ptr<Texture> m_pTexture;
	vec4 m_FixColor;
};

}
}
#endif DEFAULT_SHADER_H