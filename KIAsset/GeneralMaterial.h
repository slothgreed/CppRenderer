#ifndef GENERAL_MATERIAL_H
#define GENERAL_MATERIAL_H

namespace KI
{
namespace Asset
{

class DLL_EXPORT GeneralMaterial : public IMaterial
{
public:
	GeneralMaterial();
	~GeneralMaterial();

	virtual const MATERIAL_TYPE Type() const { return MATERIAL_TYPE::MATERIAL_TYPE_GENERAL; };

	virtual void CompileShader(IVertexBuffer* pVertexBuffer);
	virtual bool Compare(const IMaterial& material);
	void SetShader(shared_ptr<IShader> pShader) { IMaterial::SetShader(pShader); };
private:

};

}
}
#endif GENERAL_MATERIAL_H