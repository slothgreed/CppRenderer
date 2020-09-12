#ifndef BASIC_SHADING_H
#define BASIC_SHADING_H

namespace KI
{
namespace ShaderLib
{

enum BASIC_SHADING_TYPE : unsigned int 
{
	BASIC_SHADING_TYPE_FIXCOLOR,	// 固定色
	BASIC_SHADING_TYPE_TEXTURE,	// テクスチャ色
	BASIC_SHADING_TYPE_NUM,
};

class DLL_EXPORT BasicFragCode : public IShaderCode
{
public:

	BasicFragCode(BASIC_SHADING_TYPE type);
	~BasicFragCode();

	virtual void Initialize(GLuint programId) override;
	virtual void GetDefineCode(string& code) override;
	virtual bool Compare(IShaderCode* pShaderCode) override;
	virtual void Bind(shared_ptr<IShaderChunk> pShaderChunk, shared_ptr<IUniformStorage> pUniform) override;
	virtual void UnBind(shared_ptr<IShaderChunk> pShaderChunk,shared_ptr<IUniformStorage> pUniform) override;
	BASIC_SHADING_TYPE Type() { return m_Type; }

private:
	BASIC_SHADING_TYPE m_Type;
};


// no shading
class DLL_EXPORT BasicShading : public IShading
{
public:

	BasicShading(BASIC_SHADING_TYPE type);
	BasicShading(const vec4& color);
	BasicShading(shared_ptr<Texture> pTexture);

	~BasicShading();

	BASIC_SHADING_TYPE ColorType() { return m_Type; }
	void SetColor(const vec4& color);
	void SetTexture(shared_ptr<Texture> pTexture);
	const vec4& GetColor() { return m_color; }
	shared_ptr<Texture> GetTexture() { return m_pTexture; }
	virtual bool Compare(IShading* pShading);

	virtual bool NewShaderCompare(IShaderChunk* pTarget) override;
	virtual shared_ptr<IShaderCode> NewShaderCode(IShaderBuildInfo* pBuildInfo,SHADER_PROGRAM_TYPE type) override;
private:
	vec4 m_color;
	shared_ptr<Texture> m_pTexture;
	BASIC_SHADING_TYPE m_Type;

};

}
}

#endif BASIC_SHADING_H
