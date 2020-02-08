#ifndef DEFAULT_SHADER_H
#define DEFAULT_SHADER_H

namespace KI
{
class IShader;
class DefaultUniform;
class DefaultShaderDefine;

class DefaultShader : public IShader
{
	enum UNIFORM_LOCATION : unsigned short
	{
		DEFAULT_UNIFORM_COLOR_TEXTURE,
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
	void BindScene();
	shared_ptr<DefaultUniform> m_uniformParameter;
};

class DefaultUniform : public IUniform
{
public:
	DefaultUniform() :m_pTexture(nullptr), m_FixColor(vec4(1, 0, 0, 0)) {}
	SHADER_TYPE Type() { return SHADER_TYPE::SHADER_TYPE_DEFAULT; }

	void SetTexture(shared_ptr<Texture> value) { m_pTexture = value; };
	shared_ptr<Texture> GetTexture() { return m_pTexture; }
	vec4				FixColor() { return m_FixColor; }
private:
	shared_ptr<Texture> m_pTexture;
	vec4 m_FixColor;
};

class DefaultShaderDefine : public IShaderDefine
{
public:
	DefaultShaderDefine() { 
		m_useNormal = false; m_useColor = false; 
		m_useTexcoord = false; m_useTexture0 = false; };
	~DefaultShaderDefine() {};

	virtual SHADER_TYPE Type() { return SHADER_TYPE::SHADER_TYPE_DEFAULT; };
	void GetVertexDefine(string& define);
	void GetFragDefine(string& define);
	void SetShaderDefine(VERTEX_LAYOUT layout);
	virtual bool Compare(shared_ptr<IShaderDefine> shaderDefine) override;

private:
	bool m_useNormal;
	bool m_useColor;
	bool m_useTexcoord;
	bool m_useTexture0;
};

#define VERTEX_SHADER_USE_NORMAL	"#define USE_NORMAL\n"
#define VERTEX_SHADER_USE_COLOR		"#define USE_COLOR\n"
#define VERTEX_SHADER_USE_TEXCOORD	"#define USE_TEXCOORD\n"
#define FRAG_SHADER_USE_TECOORD		"#define USE_TEXCOORD\n"
#define FRAG_SHADER_USE_TEXTURE0	"#define USE_TEXTURE0\n"
}
#endif DEFAULT_SHADER_H