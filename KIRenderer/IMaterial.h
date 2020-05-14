#ifndef IMATERIAL_H
#define IMATERIAL_H

namespace KI
{
namespace Renderer
{
class DLL_EXPORT IMaterial
{
public:
	IMaterial() {};
	virtual ~IMaterial() {};

	virtual MATERIAL_TYPE Type() = 0;
	virtual bool ShaderDefineComare(IMaterial* pMaterial) = 0;
private:

};

}
}

#endif
