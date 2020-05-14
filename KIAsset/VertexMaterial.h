#ifndef VERTEX_MATERIAL_H
#define VERTEX_MATERIAL_H

namespace KI
{
namespace Asset
{
// no shading
class DLL_EXPORT VertexMaterial : public IMaterial
{
public:
	enum VERTEX_MATERIAL_TYPE
	{
		VERTEX_MATERIAL_POSITION,	// 頂点カラー
		VERTEX_MATERIAL_TEXCOORD,	// テクスチャ色
		VERTEX_MATERIAL_NORMAL,		// 法線カラー
		VERTEX_MATERIAL_DEPTH,		// デプス
	};

	VertexMaterial(VERTEX_MATERIAL_TYPE type);

	~VertexMaterial();


	VERTEX_MATERIAL_TYPE ColorType() { return m_Type; }
	virtual bool ShaderDefineComare(IMaterial* pMaterial) override;

private:
	VERTEX_MATERIAL_TYPE m_Type;

};

}
}

#endif BASIC_MATERIAL_H
