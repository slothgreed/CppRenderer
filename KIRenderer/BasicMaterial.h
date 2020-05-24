#ifndef BASIC_MATERIAL_H
#define BASIC_MATERIAL_H

namespace KI
{
namespace Renderer
{

enum BASIC_MATERIAL_TYPE : unsigned int 
{
	BASIC_MATERIAL_TYPE_FIXCOLOR,	// 固定色
	BASIC_MATERIAL_TYPE_TEXTURE,	// テクスチャ色
	BASIC_MATERIAL_TYPE_NUM,
};

class DLL_EXPORT BasicMaterialFragCode : public IShaderCode
{
public:

	BasicMaterialFragCode(BASIC_MATERIAL_TYPE type);
	~BasicMaterialFragCode();

	virtual void Initialize(GLuint programId) override;
	virtual void GetDefineCode(string& code) override;
	virtual bool Compare(IShaderCode* pShaderCode) override;
	virtual void Bind(shared_ptr<IShaderChunk> pShaderChunk) override;
	virtual void UnBind(shared_ptr<IShaderChunk> pShaderChunk) override;
	BASIC_MATERIAL_TYPE Type() { return m_Type; }

private:
	BASIC_MATERIAL_TYPE m_Type;
};


// no shading
class DLL_EXPORT BasicMaterial : public IMaterial
{
public:

	BasicMaterial(const vec4& color);
	BasicMaterial(shared_ptr<Texture> pTexture);

	~BasicMaterial();

	BASIC_MATERIAL_TYPE ColorType() { return m_Type; }
	void SetColor(const vec4& color);
	void SetTexture(shared_ptr<Texture> pTexture);
	const vec4& GetColor() { return m_color; }
	shared_ptr<Texture> GetTexture() { return m_pTexture; }
	virtual bool Compare(IMaterial* pMaterial);

	virtual bool NewShaderCompare(IShaderChunk* pTarget) override;
	virtual shared_ptr<IShaderCode> NewShaderCode(IShaderBuildInfo* pBuildInfo,SHADER_PROGRAM_TYPE type);
private:
	vec4 m_color;
	shared_ptr<Texture> m_pTexture;
	BASIC_MATERIAL_TYPE m_Type;

};

}
}

#endif BASIC_MATERIAL_H
