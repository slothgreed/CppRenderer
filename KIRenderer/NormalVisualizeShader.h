#ifndef KI_NORMAL_VISUALIZE_SHADER_H
#define KI_NORMAL_VISUALIZE_SHADER_H

namespace KI
{
namespace Renderer
{

class DLL_EXPORT NormalVisualizeUniform : public IUniform
{
public:
	SHADER_TYPE Type() { return SHADER_TYPE::SHADER_TYPE_NORMALVISUALIZE; }
	void SetLength(float value) { m_length = value; }
	float Length() { return m_length; }
private:
	float m_length;
};

class DLL_EXPORT NormalVisualizeShader : public IShader
{
	enum NORMAL_VISUALIZE_UNIFORM : unsigned char
	{
		NORMAL_VISUALIZE_UNIFORM_LENGTH,
		NORMAL_VISUALIZE_UNIFORM_NUM
	};
public:
	NormalVisualizeShader();
	~NormalVisualizeShader();
	virtual void Initialize();
	virtual void FetchUniformLocation();
	virtual void Bind(shared_ptr<IMaterial> pMaterial, shared_ptr<UniformSet> pUniform);
	virtual void UnBind(shared_ptr<IMaterial> pMaterial, shared_ptr<UniformSet> pUniform) {};

	virtual SHADER_TYPE Type() override { return SHADER_TYPE::SHADER_TYPE_NORMALVISUALIZE; }
private:
	void BindLength(float value);
	void BindScene();
	void BindLight();
};


}
}

#endif