#ifndef UNIFORM_SHADING_H
#define UNIFORM_SHADING_H

namespace KI
{
namespace ShaderLib
{
struct MaterialData
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float shining;
};

class DLL_EXPORT UniformMaterial : public UniformBuffer
{
public:
	UniformMaterial();
	~UniformMaterial();
	void Set(const MaterialData& data);
	void Bind();
private:
	MaterialData m_data;
};
}
}


#endif UNIFORM_SHADING_H