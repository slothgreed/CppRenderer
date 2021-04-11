#ifndef ARRANGE_POINT_HPP
#define ARRANGE_POINT_HPP

namespace KI
{
namespace Topology
{
class DLL_EXPORT ArrangePoint
{
public:
	ArrangePoint(HalfEdgeDS* pHalfEdgeDS, DownSampling* pDownSampling);
	~ArrangePoint();
	void Calculate(int localItrNum);
	void InitQuadPosition();
private:
	void AssignLowerByUpper(int upperIndex);
	vec3 CalcMiddlePoint(const vec3& pos0, const vec3& norm0, const vec3& pos1, const vec3& norm1);
	void CalcGridPosition(
		const vec3& pos0, const vec3& normal0, const vec3& tangent0, const vec3& quadPos0,
		const vec3& pos1, const vec3& normal1, const vec3& tangent1, const vec3& quadPos1,
		float scale, vec3* res0, vec3* res1);
	vec3 CalcFloorPosition(
		const vec3& orient, const vec3& tangent, const vec3& normal,
		const vec3& middlePos, float scale);
	vec3 CalcRoundFloorPosition(
		const vec3& orient, const vec3& tangent, const vec3& normal,
		const vec3& middlePos, float scale);
	void LocalArrange(int level);
	HalfEdgeDS* m_pHalfEdgeDS;
	DownSampling* m_pDownSampling;
};
}
}


#endif ARRANGE_POINT_HPP