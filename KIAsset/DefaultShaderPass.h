#ifndef DEFAULT_SHADERPASS_H
#define DEFAULT_SHADERPASS_H

namespace KI
{
namespace Asset
{
class DLL_EXPORT DefaultShaderPass : public IShaderPass
{
public:
	DefaultShaderPass();
	DefaultShaderPass(shared_ptr<IMaterial> pMaterial);
	~DefaultShaderPass();

	virtual const SHADERPASS_TYPE Type() const { return SHADERPASS_TYPE_DEFAULT; }
	virtual void CompileShader(IVertexBuffer* pVertexBuffer) override;
	virtual bool Compare(const IShaderPass& shaderPass) override;

	//void VisibleNormal(bool value);
	//void SetFixColor(const vec4& color);
	//void AddTexture(shared_ptr<Texture> texture);
};
}
}
#endif DEFAULT_SHADERPASS_H
