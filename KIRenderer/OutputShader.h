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
	shared_ptr<Texture> pTexture;

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
	virtual void Bind(shared_ptr<IUniform> uniform) override;
	virtual void UnBind() override;
private:
	void BindOutputTexture();
	shared_ptr<OutputUniform> m_uniformParameter;
};
}
}


#endif OUTPUT_SHADER_H