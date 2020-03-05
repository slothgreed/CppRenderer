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
	shared_ptr<Texture> pTexture;
};

class DLL_EXPORT GrayScaleShaderDefine : public IShaderDefine
{
	virtual SHADER_TYPE Type() { return SHADER_TYPE::SHADER_TYPE_GRAYSCALE; };
	virtual void GetVertexDefine(string& define) {};
	virtual void GetFragDefine(string& define) {};
	virtual bool Compare(IShaderDefine* shaderDefine) { return true; };
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

	virtual void Bind(shared_ptr<IUniform> uniform) override;
	virtual void UnBind() override;

private:
	void BindColorTexture();
	shared_ptr<Texture> m_pSource;
	shared_ptr<GrayScaleUniform> m_uniformParameter;
};
}
}


#endif GRAYSCALE_SHADERL_H
