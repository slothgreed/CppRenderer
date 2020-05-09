#ifndef GENERAL_SHADERPASS_H
#define GENERAL_SHADERPASS_H

namespace KI
{
namespace Asset
{

class DLL_EXPORT GeneralShaderPass : public IShaderPass
{
public:
	GeneralShaderPass();
	~GeneralShaderPass();

	virtual const SHADERPASS_TYPE Type() const { return SHADERPASS_TYPE::SHADERPASS_TYPE_GENERAL; };

	virtual void CompileShader(IVertexBuffer* pVertexBuffer);
	virtual bool Compare(const IShaderPass& shaderPass);
	void SetShader(shared_ptr<IShader> pShader) { IShaderPass::SetShader(pShader); };
private:

};

}
}
#endif GENERAL_SHADERPASS_H