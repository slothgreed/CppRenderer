#ifndef SPOT_LIGHT_H
#define SPOT_LIGHT_H

namespace KI
{
namespace Renderer
{
class DLL_EXPORT SpotLight : ILight
{
public:
	SpotLight();
	~SpotLight();

	const vec3& Expotent() { return m_exponent; };
	float Cutoff() { return m_cutoff; };
private:
	vec3 m_exponent;
	float m_cutoff;
};
}
}
#endif SPOT_LIGHT_H
