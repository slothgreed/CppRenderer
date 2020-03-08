#ifndef ILIGHT_H
#define ILIGHT_H

namespace KI
{
namespace Renderer
{
enum LIGHT_TYPE
{
	LIGHT_TYPE_DIRECTION,
	LIGHT_TYPE_POINT,
	LIGHT_TYPE_SPOT
};
class DLL_EXPORT ILight
{
public:
	ILight() : m_ambient(vec4(1)), m_diffuse(vec4(1)), m_speclular(vec4(1)) {};
	virtual ~ILight() {};

	virtual LIGHT_TYPE Type() = 0;
	const vec4& Ambient() { return m_ambient; };
	const vec4& Diffuse() { return m_diffuse; };
	const vec4& Specular() { return m_speclular; };
	void Ambient(vec4 value) { m_ambient = value; }
	void Diffuse(vec4 value) { m_diffuse = value; }
	void Specular(vec4 value) { m_speclular = value; }
private:
	vec4 m_ambient;
	vec4 m_diffuse;
	vec4 m_speclular;
};
}
}
#endif ILIGHT_H
