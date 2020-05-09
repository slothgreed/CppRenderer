#ifndef ADS_MATERIAL_H
#define ADS_MATERIAL_H

namespace KI
{
namespace Asset
{

class DLL_EXPORT ADSMaterial : public IMaterial
{

public:
	ADSMaterial();
	~ADSMaterial() {};

	void Set(const vec4& ambient, const vec4& diffuse, const vec4& speculat, float shinness);
private:
	vec4 m_ambient;
	vec4 m_diffuse;
	vec4 m_specular;
	float m_shinness;
};
}
}
#endif ADS_MATERIAL_H
