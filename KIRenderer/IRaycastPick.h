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
	void SetResult(PICK_TYPE type, const string& id, void* obj, float distance);
	bool Success();

private:
	PICK_TYPE m_Type;

	PICK_TYPE m_pickItemType;
	Topology::Ray* m_ray;
	float m_minDistance;
	void* m_object;
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