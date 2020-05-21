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
	~DefaultShaderPass();
	virtual const SHADERPASS_TYPE Type() const { return SHADERPASS_TYPE_DEFAULT; }
	virtual void CompileShader(shared_ptr<IVertexBuffer> pVertexBuffer) override;
	virtual bool Compare(const IShaderPass& shaderPass) override;
};
}
}
#endif DEFAULT_SHADERPASS_H
