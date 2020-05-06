#ifndef DEFAULT_MATERIAL_H
#define DEFAULT_MATERIAL_H

namespace KI
{
namespace Asset
{
class DLL_EXPORT DefaultPass : public IShaderPass
{
public:
	DefaultPass();
	~DefaultPass();

	virtual const MATERIAL_TYPE Type() const { return MATERIAL_TYPE_DEFAULT; }
	virtual void CompileShader(IVertexBuffer* pVertexBuffer) override;
	virtual bool Compare(const IShaderPass& material) override;

	void VisibleNormal(bool value);
	void SetFixColor(const vec4& color);
	void AddTexture(shared_ptr<Texture> texture);
};
}
}
#endif DEFAULT_MATERIAL_H
