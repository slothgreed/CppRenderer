#ifndef LAMBERT_SHADING_H
#define LAMBERT_SHADING_H

namespace KI
{
namespace Renderer
{
enum LAMBERT_SHADING_TYPE : unsigned int
{
	LAMBERT_SHADING_TYPE_VERTEXCOLOR,	// 頂点色
	LAMBERT_SHADING_TYPE_FIXCOLOR,		// 固定色
	LAMBERT_SHADING_TYPE_TEXTURE,		// テクスチャ色
	LAMBERT_SHADING_TYPE_NUM,
};

class DLL_EXPORT LambertFragCode : public IShaderCode
{
public:
	LambertFragCode(LAMBERT_SHADING_TYPE type);
	~LambertFragCode();

	virtual void Initialize(GLuint programId) override;
	virtual void GetDefineCode(string& code) override;
	virtual bool Compare(IShaderCode* pShaderCode) override;
	virtual void Bind(shared_ptr<IShaderChunk> pShaderChunk) override;
	virtual void UnBind(shared_ptr<IShaderChunk> pShaderChunk) override;
	LAMBERT_SHADING_TYPE Type() { return m_Type; }

private:
	LAMBERT_SHADING_TYPE m_Type;
};

class DLL_EXPORT LambertShading : public IShading
{

public:
	LambertShading(const vec4& color);
	LambertShading(shared_ptr<Texture> pTexture);

	~LambertShading() {};

	LAMBERT_SHADING_TYPE ColorType() { return m_Type; }
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
	LAMBERT_SHADING_TYPE m_Type;
};
}
}
#endif LAMBERT_SHADING_H
