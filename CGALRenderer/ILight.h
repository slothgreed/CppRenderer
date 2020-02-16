#ifndef ILIGHT_H
#define ILIGHT_H

namespace KI
{

class ILight
{
public:
	ILight() {};
	virtual ~ILight() {};

	const vec3& Ambient() { return m_ambient; };
	const vec3& Diffuse() { return m_diffuse; };
	const vec3& Specular() { return m_speclular; };

private:
	vec3 m_ambient;
	vec3 m_diffuse;
	vec3 m_speclular;
};
}

#endif ILIGHT_H
