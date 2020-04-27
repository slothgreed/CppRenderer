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
	virtual void Bind(shared_ptr<IShader> pShader) override;
	virtual void UnBind(shared_ptr<IShader> pShader) override;
	virtual void CompileShader(IVertexBuffer* pVertexBuffer) override;
	virtual bool Compare(const IMaterial& material) override;

	void VisibleNormal(bool value);
	void SetFixColor(vec4 color);
	void AddTexture(shared_ptr<Texture> texture);
private:
	shared_ptr<UniformSet> m_pUniform;
};
}
}
#endif DEFAULT_MATERIAL_H
