#ifndef DEFAULT_MATERIAL_H
#define DEFAULT_MATERIAL_H

namespace KI
{
namespace Asset
{
class DLL_EXPORT DefaultMaterial : public IMaterial
{
public:
	DefaultMaterial();
	~DefaultMaterial();

	virtual const MATERIAL_TYPE Type() const { return MATERIAL_TYPE_DEFAULT; }
	virtual void CompileShader(IVertexBuffer* pVertexBuffer) override;
	virtual bool Compare(const IMaterial& material) override;

	void VisibleNormal(bool value);
	void SetFixColor(const vec4& color);
	void AddTexture(shared_ptr<Texture> texture);
};
}
}
#endif DEFAULT_MATERIAL_H
