#ifndef ADS_MATERIAL_H
#define ADS_MATERIAL_H

namespace KI
{
namespace Renderer
{

class DLL_EXPORT ADSMaterial : public IMaterial
{

public:
	ADSMaterial();
	~ADSMaterial() {};

	void Set(const vec4& ambient, const vec4& diffuse, const vec4& speculat, float shinness);

	virtual shared_ptr<IShaderCode> NewShaderCode(IShaderBuildInfo* pBuildInfo,SHADER_PROGRAM_TYPE type) override;

private:
	vec4 m_ambient;
	vec4 m_diffuse;
	vec4 m_specular;
	float m_shinness;
};
}
}
#endif ADS_MATERIAL_H
