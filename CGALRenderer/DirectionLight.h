#ifndef DIRECTION_LIGHT_H
#define DIRECTION_LIGHT_H

namespace KI
{
class DirectionLight
{
public:
	DirectionLight();
	~DirectionLight();

	const vec3& Direction() { return m_direction; }

private:
	vec3 m_direction;

};
}

#endif DIRECTION_LIGHT_H
