#ifndef NORMALVISUALIZE_SHADING_H
#define NORMALVISUALIZE_SHADING_H

namespace KI
{
namespace ShaderLib
{
class DLL_EXPORT NormalVisualizeShading : public IShading
{
public:
	SHADER_TYPE Type() { return SHADER_TYPE::SHADER_TYPE_GRAYSCALE; }

	void SetLength(float value) { m_Length = value; }
	float GetLength() { return m_Length; }

	virtual bool NewShaderCompare(IShaderChunk* pTarget) override;
	virtual shared_ptr<IShaderCode> NewShaderCode(IShaderBuildInfo* pBuildInfo,SHADER_PROGRAM_TYPE type);

private:
	float m_Length;
};

class DLL_EXPORT NormalVisualizeGeomCode : public IShaderCode
{
	enum NORMAL_VISUALIZE_UNIFORM : unsigned short
	{
		NORMAL_VISUALIZE_UNIFORM_LENGTH,
		NORMAL_VISUALIZE_UNIFORM_NUM
	};

public:

	NormalVisualizeGeomCode();
	~NormalVisualizeGeomCode();

	virtual SHADER_TYPE Type() { return SHADER_TYPE::SHADER_TYPE_GRAYSCALE; }

	virtual void Initialize(GLuint programId) override;

	virtual bool Compare(IShaderCode* pShaderCode) override;
	virtual void Bind(shared_ptr<IShaderChunk> pShaderChunk,shared_ptr<IUniformStorage> pUniform) override;
	virtual void UnBind(shared_ptr<IShaderChunk> pShaderChunk,shared_ptr<IUniformStorage> pUniform) override {};


private:
	void BindLength(float length);
	shared_ptr<Texture> m_pSource;
};
}
}
#endif NORMALVISUALIZE_SHADING_H