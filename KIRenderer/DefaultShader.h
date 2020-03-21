#ifndef DEFAULT_SHADER_H
#define DEFAULT_SHADER_H

namespace KI
{
namespace Renderer
{
class DefaultUniform;
class DefaultShaderDefine;

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
	DefaultUniform() :m_pTexture(nullptr), m_FixColor(vec4(0, 1, 0, 1)) {}
	SHADER_TYPE Type() { return SHADER_TYPE::SHADER_TYPE_DEFAULT; }

	void SetTexture(shared_ptr<Texture> value) { m_pTexture = value; };
	void SetFixColor(vec4 value) { m_FixColor = value; };
	shared_ptr<Texture> GetTexture() { return m_pTexture; }
	vec4				FixColor() { return m_FixColor; }
private:
	shared_ptr<Texture> m_pTexture;
	vec4 m_FixColor;
};

class DLL_EXPORT DefaultShaderDefine : public IShaderDefine
{
public:
	DefaultShaderDefine() {
		m_useGBuffer = false;
		m_useNormal = false; m_useColor = false; 
		m_useTexcoord = false; m_useTexture0 = false;
		m_useShading = false; m_useInstance = false;};
	~DefaultShaderDefine() {};

	virtual SHADER_TYPE Type() { return SHADER_TYPE::SHADER_TYPE_DEFAULT; };
	void GetVertexDefine(string& define);
	void GetFragDefine(string& define);
	void SetShaderDefine(GLuint layout);
	virtual bool Compare(IShaderDefine* shaderDefine) override;

	void SetUseGBuffer(bool value) { m_useGBuffer = value; }
	void SetUseNormal(bool value) { m_useNormal = value; };
	void SetUseColor(bool value) { m_useColor = value; };
	void SetUseTexcoord(bool value) { m_useTexcoord = value; };
	void SetUseTexture0(bool value) { m_useTexture0 = value; };
	void SetUseInstance(bool value) { m_useInstance = value; };
	void SetShading(bool value) { m_useShading = value; }

	bool UseGBuffer() const { return m_useGBuffer; }
	bool UseNormal() const { return m_useNormal; };
	bool UseColor() const { return m_useColor; };
	bool UseTexcoord() const { return m_useTexcoord; };
	bool UseTexture0() const { return m_useTexture0; };
	bool UseInstance() const { return m_useInstance; };
	bool UseShading() const { return m_useShading; }
	
private:
	bool m_useGBuffer;
	bool m_useNormal;
	bool m_useColor;
	bool m_useTexcoord;
	bool m_useTexture0;
	bool m_useInstance;
	bool m_useShading;
};

#define USE_NORMAL	 "#define USE_NORMAL\n"
#define USE_COLOR	 "#define USE_COLOR\n"
#define USE_TEXCOORD "#define USE_TEXCOORD\n"
#define USE_TEXTURE0 "#define USE_TEXTURE0\n"
#define USE_GBUFFER	 "#define USE_GBUFFER\n"
#define USE_SHADING	 "#define USE_SHADING\n"
#define USE_INSTANCE "#define USE_INSTANCE\n"
}
}
#endif DEFAULT_SHADER_H