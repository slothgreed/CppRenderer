#ifndef UNIFORM_LIGHT_H
#define UNIFORM_LIGHT_H

namespace KI
{
namespace ShaderLib
{

// https://en.wikibooks.org/wiki/GLSL_Programming/GLUT/Smooth_Specular_Highlights
struct DLL_EXPORT LightData
{
	vec4 position;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec4 spotDirection;
	float spotCutoff;
	float spotExponent;
	float constantAttenuation;
	float linearAttenuation;
	float quadraticAttenuation;
};

class DLL_EXPORT UniformLight : public UniformBuffer
{
public:
	UniformLight();
	~UniformLight();
	void Set(const LightData& data);
};
}
}


#endif UNIFORM_LIGHT_H