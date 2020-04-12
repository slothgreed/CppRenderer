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
	virtual void Bind();
	virtual void UnBind();
	virtual shared_ptr<IShader> CompileShader(IVertexBuffer* pVertexBuffer) override;
	virtual bool Compare(const IMaterial& material);

	void VisibleNormal(bool value);
	void SetFixColor(vec4 color);
	void AddTexture(shared_ptr<Texture> texture);
private:
	shared_ptr<UniformSet> m_pUniform;
};
}
}
#endif DEFAULT_MATERIAL_H
