#ifndef VERTEX_MATERIAL_H
#define VERTEX_MATERIAL_H

namespace KI
{
namespace Renderer
{
enum VERTEX_MATERIAL_TYPE
{
	VERTEX_MATERIAL_POSITION,	// 頂点カラー
	VERTEX_MATERIAL_TEXCOORD,	// テクスチャ色
	VERTEX_MATERIAL_COLOR,		// 頂点カラー
	VERTEX_MATERIAL_NORMAL,		// 法線カラー
	VERTEX_MATERIAL_DEPTH,		// デプス
};
// no shading
class DLL_EXPORT VertexMaterial : public IMaterial
{
public:
	VertexMaterial(VERTEX_MATERIAL_TYPE type);
	~VertexMaterial();

	bool Compare(IMaterial* pMaterial);

	VERTEX_MATERIAL_TYPE Type() { return m_Type; }

	virtual bool NewShaderCompare(IShaderChunk* pTarget) override;
	virtual shared_ptr<IShaderCode> NewShaderCode(IShaderBuildInfo* pBuildInfo,SHADER_PROGRAM_TYPE type) override;

private:
	VERTEX_MATERIAL_TYPE m_Type;

};

class DLL_EXPORT VertexMaterialVertexCode : public DefaultVertexCode
{
public:

	VertexMaterialVertexCode(VERTEX_MATERIAL_TYPE type);
	~VertexMaterialVertexCode() {};

	virtual void Initialize(GLuint programId) {};
	virtual void SetViewVertexType(VERTEX_MATERIAL_TYPE type) { m_Type = type; }
	virtual void GetDefineCode(string& code) override;
	virtual bool Compare(IShaderCode* pShaderCode) override;
	virtual void Bind(shared_ptr<IShaderChunk> pShaderChunk) override {};
	virtual void UnBind(shared_ptr<IShaderChunk> pShaderChunk) override {};

	VERTEX_MATERIAL_TYPE Type() { return m_Type; }
private:
	VERTEX_MATERIAL_TYPE m_Type;
};

class DLL_EXPORT VertexMaterialFragCode : public IShaderCode
{
public:

	VertexMaterialFragCode();
	~VertexMaterialFragCode() {};

	virtual void Initialize(GLuint programId) {};
	virtual bool Compare(IShaderCode* pShaderCode) override { return true; };
	virtual void Bind(shared_ptr<IShaderChunk> pShaderChunk)  override {};
	virtual void UnBind(shared_ptr<IShaderChunk> pShaderChunk)  override {};

private:
	VERTEX_MATERIAL_TYPE m_Type;
};
}
}

#endif VERTEX_MATERIAL_H
