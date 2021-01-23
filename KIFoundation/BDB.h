#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H
namespace KI
{
namespace Foundation
{
class DLL_EXPORT BDB
{
public:
	BDB();
	BDB(vec3 min, vec3 max);
	void Set(vec3 min, vec3 max);
	void Apply(const vec3& position);
	void Apply(const BDB& bdb);
	float SurfaceArea() { return m_surfaceArea; }
	const vec3& Min() const { return m_min; }
	const vec3& Max() const { return m_max; }
	const vec3& Center() const { return m_center; }
	float MaxEdgeLength();
	string ToString();
	~BDB();

private:
	vec3 m_min;
	vec3 m_max;
	vec3 m_center;
	float m_surfaceArea;
	
};
}
}
#endif BOUNDING_BOX_H