#ifndef GET_COLOR_CODE_H
#define GET_COLOR_CODE_H
namespace KI
{
namespace ShaderLib
{

enum SHADING_COLOR_TYPE : unsigned int
{
	SHADING_COLOR_TYPE_VERTEXCOLOR,	// 頂点色
	SHADING_COLOR_TYPE_FIXCOLOR,		// 固定色
	SHADING_COLOR_TYPE_TEXTURE,		// テクスチャ色
	SHADING_COLOR_TYPE_NUM,
};

// Shadingが継承する。
class DLL_EXPORT IHasGetColor
{
public:
	SHADING_COLOR_TYPE ColorType() { return m_ColorType; }
	virtual void SetColor(const vec4& color);
	virtual void SetTexture(shared_ptr<Texture> pTexture);
	virtual const vec4& GetColor() { return m_color; }
	virtual shared_ptr<Texture> GetTexture() { return m_pTexture;}
private:
	vec4 m_color;
	shared_ptr<Texture> m_pTexture;
	SHADING_COLOR_TYPE m_ColorType;
};

//ShadingCodeが継承する。
class DLL_EXPORT GetColorCode : public IShaderCode
{
public:
	GetColorCode(SHADING_COLOR_TYPE type);
	~GetColorCode();
	virtual void Initialize(GLuint programId);
	virtual void GetDefineCode(string& code);
	virtual bool Compare(IShaderCode* pShaderCode);
	virtual void Bind(shared_ptr<IShaderChunk> pShaderChunk, shared_ptr<IUniformStorage> pUniform);
	virtual void UnBind(shared_ptr<IShaderChunk> pShaderChunk, shared_ptr<IUniformStorage> pUniform);
	SHADING_COLOR_TYPE Type() { return m_Type; }

private:
	SHADING_COLOR_TYPE m_Type;
};

}
}

#endif //GET_COLOR_CODE_H
