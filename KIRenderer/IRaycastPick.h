#ifndef IRAYCAST_PICK_H
#define IRAYCAST_PICK_H
namespace KI
{

namespace Topology
{
	class Ray;
};

namespace Renderer
{

class DLL_EXPORT RaycastPickInfo
{
public:
	RaycastPickInfo(PICK_TYPE type, Topology::Ray* ray) { m_Type = type; m_ray = ray; };
	~RaycastPickInfo() {};

	PICK_TYPE Type() { return m_Type; }
	const Topology::Ray& GetRay() { return *m_ray; };
	float MinDistance() { return m_minDistance; };
	void SetResult(PICK_TYPE type, const string& id, int first, int count, float distance);
	bool Success();

	void GetSelectRegion(int& first, int& count) { first = m_first; count = m_count; }
private:
	PICK_TYPE m_Type;

	PICK_TYPE m_pickItemType;
	Topology::Ray* m_ray;
	float m_minDistance;
	int m_first;
	int m_count;
	string m_identifier;
};

class DLL_EXPORT IRaycastPick
{
public:
	IRaycastPick() {};
	~IRaycastPick() {};

	virtual void RaycastPick(RaycastPickInfo& pickInfo) = 0;
private:
};
}
}

#endif