#ifndef SSLIC_SHADER_H
#define SSLIC_SHADER_H

namespace KI
{

class SSLICShader : IShader
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
	void BindColorTexture();
private:

};

}

#endif SSLIC_SHADER_H