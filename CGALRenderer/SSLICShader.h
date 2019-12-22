#ifndef SSLIC_SHADER_H
#define SSLIC_SHADER_H

namespace KI
{

class SSLICUniform : public IUniform
{
public:
	virtual SHADER_TYPE Type() override { return SHADER_TYPE::SHADER_TYPE_SSLIC; }
	shared_ptr<Texture> pTexture;
};


class SSLICShader : public IShader
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
	virtual void Bind(shared_ptr<IUniform> uniform) override;
	virtual void UnBind() override;

private:
	void BindColorTexture();
	shared_ptr<SSLICUniform> m_uniformParameter;
};

}

#endif SSLIC_SHADER_H