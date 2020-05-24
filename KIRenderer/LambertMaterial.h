#ifndef LAMBERT_MATERIAL_H
#define LAMBERT_MATERIAL_H

namespace KI
{
namespace Renderer
{
enum LAMBERT_MATERIAL_TYPE : unsigned int
{
	LAMBERT_MATERIAL_TYPE_VERTEXCOLOR,	// 頂点色
	LAMBERT_MATERIAL_TYPE_FIXCOLOR,	// 固定色
	LAMBERT_MATERIAL_TYPE_TEXTURE,		// テクスチャ色
	LAMBERT_MATERIAL_TYPE_NUM,
};

class DLL_EXPORT LambertMaterialFragCode : public IShaderCode
{
public:
	LambertMaterialFragCode(LAMBERT_MATERIAL_TYPE type);
	~LambertMaterialFragCode();

	virtual void Initialize(GLuint programId) override;
	virtual void GetDefineCode(string& code) override;
	virtual bool Compare(IShaderCode* pShaderCode) override;
	virtual void Bind(shared_ptr<IShaderChunk> pShaderChunk) override;
	virtual void UnBind(shared_ptr<IShaderChunk> pShaderChunk) override;
	LAMBERT_MATERIAL_TYPE Type() { return m_Type; }

private:
	LAMBERT_MATERIAL_TYPE m_Type;
};

class DLL_EXPORT LambertMaterial : public IMaterial
{

public:
	LambertMaterial(const vec4& color);
	LambertMaterial(shared_ptr<Texture> pTexture);

	~LambertMaterial() {};

	LAMBERT_MATERIAL_TYPE ColorType() { return m_Type; }
	void SetColor(const vec4& color);
	void SetTexture(shared_ptr<Texture> pTexture);
	const vec4& GetColor() { return m_color; }
	virtual bool Compare(IMaterial* pMaterial);
	shared_ptr<Texture> GetTexture() { return m_pTexture; }
	virtual bool NewShaderCompare(IShaderChunk* pTarget) override;
	virtual shared_ptr<IShaderCode> NewShaderCode(IShaderBuildInfo* pBuildInfo,SHADER_PROGRAM_TYPE type) override;

private:
	vec4 m_color;
	shared_ptr<Texture> m_pTexture;
	LAMBERT_MATERIAL_TYPE m_Type;
};
}
}
#endif LAMBERT_MATERIAL_H
