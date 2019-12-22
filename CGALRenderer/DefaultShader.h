#ifndef DEFAULT_SHADER_H
#define DEFAULT_SHADER_H

namespace KI
{
class IShader;

class DefaultUniform : public IUniform
{
public:
	DefaultUniform() :pTexture(nullptr) {}
	SHADER_TYPE Type() { return SHADER_TYPE::SHADER_TYPE_DEFAULT; }
	shared_ptr<Texture> pTexture;
};

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
	static void GetVertexShaderDefine(VERTEX_LAYOUT layout, ShaderBuildInfo& buildInfo);
	static void GetFragShaderDefine(VERTEX_LAYOUT layout, ShaderBuildInfo& shaderDefine);

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


#define VERTEX_SHADER_USE_NORMAL	"#define USE_NORMAL\n"
#define VERTEX_SHADER_USE_COLOR		"#define USE_COLOR\n"
#define VERTEX_SHADER_USE_TEXCOORD	"#define USE_TEXCOORD\n"
#define FRAG_SHADER_USE_TECOORD		"#define USE_TEXCOORD\n"
#define FRAG_SHADER_USE_TEXTURE0	"#define USE_TEXTURE0\n"
}
#endif DEFAULT_SHADER_H