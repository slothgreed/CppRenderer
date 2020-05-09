#ifndef UNIFORM_MATERIAL_H
#define UNIFORM_MATERIAL_H

namespace KI
{
namespace Renderer
{
struct MaterialData
{
	vec4 direction;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
};

class DLL_EXPORT UniformMaterial : public UniformBuffer
{
public:
	UniformMaterial();
	~UniformMaterial();
	void Set(const MaterialData& data);
};
}
}


#endif UNIFORM_MATERIAL_H