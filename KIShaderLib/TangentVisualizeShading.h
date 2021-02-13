#ifndef TANGENT_VISUALIZE_SHADING_H
#define TANGENT_VISUALIZE_SHADING_H

namespace KI
{
namespace ShaderLib
{
class DLL_EXPORT TangentVisualizeShading : public IHasShading
{
public:
	SHADER_TYPE Type() { return SHADER_TYPE::SHADER_TYPE_TANGENTVISUALIZE; }

	TangentVisualizeShading(vec4 color, bool visibleNormal);
	~TangentVisualizeShading();

	void SetOffset(float offset) { m_Offset = offset; }
	void SetLength(float value) { m_Length = value; }
	void SetColor(const vec4& color);
	float GetOffset() { return m_Offset; }
	float GetLength() { return m_Length; }
	bool GetVisualizeNormal() { return m_visibleNormal; }

	virtual bool NewShaderCompare(IShaderChunk* pTarget) override;
	virtual shared_ptr<IShaderCode> NewShaderCode(IShaderBuildInfo* pBuildInfo,SHADER_PROGRAM_TYPE type) override;

private:
	float m_Offset;
	float m_Length;
	vec4 m_Color;
	bool m_visibleNormal;
};

class TangentVisualizeVertexCode : public IShaderCode
{
public:
	enum ATTRIBUTE
	{
		POSITION = 0,
		NORMAL = 1,
		TANGENT = 2,
	};

	TangentVisualizeVertexCode()
		:IShaderCode(
			string(SHADER_DIRECTORY) +
			string(SHADER_TANGENTVIS) +
			string(SHADER_EXT_VERTEX)) {};
	~TangentVisualizeVertexCode() {};
	virtual SHADER_TYPE Type() { return SHADER_TYPE::SHADER_TYPE_TANGENTVISUALIZE; }
	

private:
	virtual void Initialize(GLuint programId) override {};
	virtual bool Compare(IShaderCode* pShaderCode) override { return true; };
	virtual void GetIncludeCode(vector<shared_ptr<IShaderCode>>& pShaderCodes);
	virtual void Bind(shared_ptr<IShaderChunk> pShaderChunk, shared_ptr<IUniformStorage> pUniform) override {};
	virtual void UnBind(shared_ptr<IShaderChunk> pShaderChunk, shared_ptr<IUniformStorage> pUniform) override {};
};

class DLL_EXPORT TangentVisualizeGeomCode : public IShaderCode
{
	enum TANGENT_VISUALIZE_UNIFORM : unsigned short
	{
		TANGENT_VISUALIZE_UNIFORM_LENGTH,
		TANGENT_VISUALIZE_UNIFORM_OFFSET,
		TANGENT_VISUALIZE_UNIFORM_NUM
	};

public:

	TangentVisualizeGeomCode(bool visibleNormal);
	~TangentVisualizeGeomCode();

	virtual SHADER_TYPE Type() { return SHADER_TYPE::SHADER_TYPE_TANGENTVISUALIZE; }

	virtual void GetDefineCode(string& code) override;
	virtual void Initialize(GLuint programId) override;
	virtual bool Compare(IShaderCode* pShaderCode) override;
	virtual void Bind(shared_ptr<IShaderChunk> pShaderChunk,shared_ptr<IUniformStorage> pUniform) override;
	virtual void UnBind(shared_ptr<IShaderChunk> pShaderChunk,shared_ptr<IUniformStorage> pUniform) override {};


private:
	bool m_visibleNormal;
	void BindLength(float length);
	void BindOffset(float length);
	shared_ptr<Texture> m_pSource;
};
}
}
#endif TANGENT_VISUALIZE_SHADING_H