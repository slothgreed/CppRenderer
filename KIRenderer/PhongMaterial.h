#ifndef PHONG_MATERIAL_H
#define PHONG_MATERIAL_H

namespace KI
{
namespace Renderer
{

enum PHONG_MATERIAL_TYPE : unsigned int
{
	PHONG_MATERIAL_TYPE_PHONG,
	PHONG_MATERIAL_TYPE_BLIN,
	PHONG_MATERIAL_TYPE_COOKTRANCE,
	PHONG_MATERIAL_TYPE_NUM
};

struct ADSMaterialData
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
};

class PhongMaterialFragCode : public IShaderCode
{
public:
	PhongMaterialFragCode();
	~PhongMaterialFragCode();

private:

};

class DLL_EXPORT PhongMaterial : public IMaterial
{
public:
	PhongMaterial(PHONG_MATERIAL_TYPE type, const ADSMaterialData& data);
	~PhongMaterial();

	void Set(const ADSMaterialData& adsData);
private:
	PHONG_MATERIAL_TYPE m_Type;
	ADSMaterialData m_ADSData;
	
};

}
}
#endif
