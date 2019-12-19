#ifndef OUTPUT_SHADER_H
#define OUTPUT_SHADER_H

namespace KI
{

class OutputShader : public IShader
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
	void BindOutputTexture();

private:

};

}


#endif OUTPUT_SHADER_H