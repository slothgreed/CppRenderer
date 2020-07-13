#ifndef LAMBERT_SHADING_H
#define LAMBERT_SHADING_H

namespace KI
{
namespace ShaderLib
{

class DLL_EXPORT LambertFragCode : public IShaderCode
{
public:
	LambertFragCode(SHADING_COLOR_TYPE type);
	~LambertFragCode();

	virtual void Initialize(GLuint programId) override;
	virtual void GetDefineCode(string& code) override;
	virtual bool Compare(IShaderCode* pShaderCode) override;
	virtual void Bind(shared_ptr<IShaderChunk> pShaderChunk,shared_ptr<IUniformStorage> pUniform) override;
	virtual void UnBind(shared_ptr<IShaderChunk> pShaderChunk,shared_ptr<IUniformStorage> pUniform) override;

private:
	shared_ptr<GetColorCode> m_pColorCode;
};

class DLL_EXPORT LambertShading : public IShading
{

public:
	LambertShading(const vec4& color);
	LambertShading(shared_ptr<Texture> pTexture);

	~LambertShading() {};

	SHADING_COLOR_TYPE ColorType() { return m_Type; }
	void SetColor(const vec4& color);
	void SetTexture(shared_ptr<Texture> pTexture);
	const vec4& GetColor() { return m_color; }
	virtual bool Compare(IShading* pShading);
	shared_ptr<Texture> GetTexture() { return m_pTexture; }
	virtual bool NewShaderCompare(IShaderChunk* pTarget) override;
	virtual shared_ptr<IShaderCode> NewShaderCode(IShaderBuildInfo* pBuildInfo,SHADER_PROGRAM_TYPE type) override;

private:
	vec4 m_color;
	shared_ptr<Texture> m_pTexture;
	SHADING_COLOR_TYPE m_Type;
};
}
}
#endif LAMBERT_SHADING_H
