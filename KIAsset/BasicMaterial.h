#ifndef BASIC_MATERIAL_H
#define BASIC_MATERIAL_H

namespace KI
{
namespace Asset
{
class DLL_EXPORT BasicMaterialVertexCode : public IShaderCode
{
public:
	BasicMaterialVertexCode();
	~BasicMaterialVertexCode() {};
	SHADER_TYPE Type() { return SHADER_TYPE::SHADER_TYPE_BASICMATERIAL; };
	string GetCode() { return m_Code; }
private:
	string m_Code;
};

class DLL_EXPORT BasicMaterialFragCode : public IShaderCode
{
public:
	BasicMaterialFragCode();
	~BasicMaterialFragCode() {};
	SHADER_TYPE Type() { return SHADER_TYPE::SHADER_TYPE_BASICMATERIAL; };

	string GetCode() { return m_Code; }
private:
	string m_Code;
};

// no shading
class DLL_EXPORT BasicMaterial : public IMaterial
{
public:
	enum BASIC_MATERIAL_TYPE
	{
		BASIC_MATERIAL_TYPE_VERTEXCOLOR,// 頂点カラー
		BASIC_MATERIAL_TYPE_NORMAL,		// 法線カラー
		BASIC_MATERIAL_TYPE_TEXCOORD,	// テクスチャ
		BASIC_MATERIAL_TYPE_DEPTH,		// デプス
		BASIC_MATERIAL_TYPE_FIXCOLOR,	// 固定色
		BASIC_MATERIAL_TYPE_TEXTURE,	// テクスチャ色
	};

	BasicMaterial();
	BasicMaterial(const vec4& color);
	BasicMaterial(shared_ptr<Texture> pTexture);
	BasicMaterial(BASIC_MATERIAL_TYPE type);

	~BasicMaterial();

	BASIC_MATERIAL_TYPE ColorType() { return m_Type; }
	void SetColor(const vec4& color);
	void SetTexture(shared_ptr<Texture> pTexture);
	void GetEmbeddedCode(SHADER_PROGRAM_TYPE& type, string& code);
	virtual string GetName() { return "BasicMaterial"; };
	vector<GLint> m_uniformLocation;

	enum UNIFORM_LOCATION : unsigned short
	{
		BASICMATERIAL_UNIFORM_COLOR_TEXTURE,
		BASICMATERIAL_UNIFORM_FIX_COLOR,
		BASICMATERIAL_UNIFORM_NUM
	};
	virtual void Initialize() override;
	virtual void FetchUniformLocation(GLuint programId) override;
	virtual void Bind() override;
	virtual void UnBind() override;
private:
	void BindColorTexture();
	void BindFixColor();
	vec4 m_color;
	shared_ptr<Texture> m_pTexture;
	BASIC_MATERIAL_TYPE m_Type;
};

}
}

#endif BASIC_MATERIAL_H
