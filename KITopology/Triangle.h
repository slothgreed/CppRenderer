#ifndef KI_TOPOLOGY_TRIANGLE_H
#define KI_TOPOLOGY_TRIANGLE_H

namespace KI
{
namespace Topology
{
class Triangle
{
public:
	Triangle() {}

	Triangle(vec3 pos0, vec3 pos1, vec3 pos2) :
		m_position0(pos0),
		m_position1(pos1),
		m_position2(pos2) {};
	~Triangle() {};

	inline void SetPosition(vec3 pos0, vec3 pos1, vec3 pos2) 
	{
		m_position0 = pos0;
		m_position1 = pos1;
		m_position2 = pos2;
	}

	inline void GetPosition(vec3* pos0, vec3* pos1, vec3* pos2) 
	{
		*pos0 = m_position0;
		*pos1 = m_position1;
		*pos2 = m_position2;
	}

	inline void SetIndex(int index)
	{
		m_Index = index;
	}

	int GetIndex()
	{
		return m_Index;
	}

	vec3 Gravity()
	{
		return (m_position0 + m_position1 + m_position2) * vec3(1.0 / 3);
	}
private:
	int m_Index;
	vec3 m_position0;
	vec3 m_position1;
	vec3 m_position2;
};
}
}


#endif KI_TOPOLOGY_TRIANGLE_H