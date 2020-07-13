#ifndef PHONG_SHADING_H
#define PHONG_SHADING_H

namespace KI
{
namespace ShaderLib
{

enum PHONG_SHADING_TYPE : unsigned int
{
	PHONG_SHADING_TYPE_PHONG,
	PHONG_SHADING_TYPE_BLIN,
	PHONG_SHADING_TYPE_COOKTRANCE,
	PHONG_SHADING_TYPE_NUM
};

struct ADSShadingData
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
};

class PhongShadingFragCode : public IShaderCode
{
public:
	PhongShadingFragCode();
	~PhongShadingFragCode();

private:

};

class DLL_EXPORT PhongShading : public IShading
{
public:
	PhongShading(PHONG_SHADING_TYPE type, const ADSShadingData& data);
	~PhongShading();

	void Set(const ADSShadingData& adsData);
private:
	PHONG_SHADING_TYPE m_Type;
	ADSShadingData m_ADSData;
	
};

}
}
#endif
