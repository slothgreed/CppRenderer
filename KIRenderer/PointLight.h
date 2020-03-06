#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

namespace KI
{
namespace Renderer
{
class DLL_EXPORT PointLight
{
public:
	PointLight();
	~PointLight();

	const vec3& Position() { return m_position; }
private:

	vec3 m_position;
};
}
}
#endif POINT_LIGHT_H
