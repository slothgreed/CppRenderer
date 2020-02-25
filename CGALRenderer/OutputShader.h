#ifndef OUTPUT_SHADER_H
#define OUTPUT_SHADER_H

namespace KI
{

class OutputUniform : public IUniform
{
public:
	virtual SHADER_TYPE Type() override { return SHADER_TYPE::SHADER_TYPE_OUTPUT; }
	shared_ptr<Texture> pTexture;
};

class OutputShaderDefine : public IShaderDefine
{
	virtual SHADER_TYPE Type() { return SHADER_TYPE::SHADER_TYPE_OUTPUT; };
	virtual void GetVertexDefine(string& define) {};
	virtual void GetFragDefine(string& define) {};
	virtual bool Compare(IShaderDefine* shaderDefine) { return true; };
};
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
	virtual void Bind(shared_ptr<IUniform> uniform) override;
	virtual void UnBind() override;
private:
	void BindOutputTexture();
	shared_ptr<OutputUniform> m_uniformParameter;
};

}


#endif OUTPUT_SHADER_H