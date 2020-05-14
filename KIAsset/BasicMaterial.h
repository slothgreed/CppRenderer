#ifndef BASIC_MATERIAL_H
#define BASIC_MATERIAL_H

namespace KI
{
namespace Asset
{

class DLL_EXPORT BasicMaterialFragCode : public IShaderCode
{
public:
	BasicMaterialFragCode();
	~BasicMaterialFragCode();

private:

};


// no shading
class DLL_EXPORT BasicMaterial : public IMaterial
{
public:
	enum BASIC_MATERIAL_TYPE
	{
		BASIC_COLOR_TYPE_FIX,		// 固定色
		BASIC_COLOR_TYPE_TEXTURE,	// テクスチャ色
	};

	BasicMaterial(const vec4& color);
	BasicMaterial(shared_ptr<Texture> pTexture);

	~BasicMaterial();

	BASIC_MATERIAL_TYPE ColorType() { return m_Type; }
	void SetColor(const vec4& color);
	void SetTexture(shared_ptr<Texture> pTexture);

	virtual bool ShaderDefineComare(IMaterial* pMaterial) override;
private:
	vec4 m_color;
	shared_ptr<Texture> m_pTexture;
	BASIC_MATERIAL_TYPE m_Type;

};

}
}

#endif BASIC_MATERIAL_H
