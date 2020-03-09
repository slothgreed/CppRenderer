#ifndef UNIFORM_LIGHT_H
#define UNIFORM_LIGHT_H

namespace KI
{
namespace Renderer
{
struct LightData
{
	vec4 direction;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
};

class DLL_EXPORT UniformLight : public UniformBuffer
{
public:
	UniformLight();
	~UniformLight();
	void Set(const LightData& data);
	void Set(ILight* pLight);
};
}
}


#endif UNIFORM_LIGHT_H