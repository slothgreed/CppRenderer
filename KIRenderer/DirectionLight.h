#ifndef DIRECTION_LIGHT_H
#define DIRECTION_LIGHT_H

namespace KI
{
namespace Renderer
{

class DLL_EXPORT DirectionLight : public ILight
{
public:
	DirectionLight();
	~DirectionLight();

	virtual LIGHT_TYPE Type() override { return LIGHT_TYPE_DIRECTION; }

	const vec3& Direction() { return m_direction; }
	void SetDirection(vec3 direction) { m_direction = direction; }
private:
	vec3 m_direction;
};
}
}
#endif DIRECTION_LIGHT_H
