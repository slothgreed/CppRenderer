#ifndef IRAYCAST_PICK_H
#define IRAYCAST_PICK_H
namespace KI
{

namespace Topology
{
	class Ray;
};

namespace Asset
{

class DLL_EXPORT RaycastPickInfo
{
public:
	RaycastPickInfo(PICK_TYPE type, Topology::Ray* ray);
	~RaycastPickInfo() {};

	PICK_TYPE Type() { return m_Type; }
	const Topology::Ray& GetRay() { return *m_ray; };
	float MinDistance() { return m_minDistance; };
	void SetResult(PICK_TYPE type, const string& id, int first, int count, vec3 position, float distance);
	bool Success();

	const vec3& GetSelectPosition() const { return m_position; }
	void GetSelectRegion(int& first, int& count) { first = m_first; count = m_count; }
private:
	PICK_TYPE m_Type;

	PICK_TYPE m_pickItemType;
	Topology::Ray* m_ray;
	float m_minDistance;
	int m_first;
	int m_count;
	string m_identifier;
	vec3 m_position;
};

class DLL_EXPORT IRaycastPick
{
public:
	IRaycastPick() {};
	virtual ~IRaycastPick() {};

	virtual void RaycastPick(RaycastPickInfo& pickInfo) = 0;
private:
};
}
}

#endif