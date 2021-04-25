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
	const std::vector<float>& ErrorValue() { return m_error; }
private:
	void InitQuadPosition();
	void AssignLowerByUpper(int upperIndex);
	void CalcErrorValue();
	vec3 CalcMiddlePoint(const vec3& pos0, const vec3& norm0, const vec3& pos1, const vec3& norm1);
	void CalcGridPosition(
		const vec3& pos0, const vec3& normal0, const vec3& tangent0, const vec3& quadPos0,
		const vec3& pos1, const vec3& normal1, const vec3& tangent1, const vec3& quadPos1,
		float scale, vec3* res0, vec3* res1);
	void CalcGridPosition2();
	vec3 CalcFloorPosition(
		const vec3& orient, const vec3& tangent, const vec3& normal,
		const vec3& middlePos, float scale);
	vec3 CalcRoundFloorPosition(
		const vec3& orient, const vec3& tangent, const vec3& normal,
		const vec3& pos, float scale);
	void LocalArrange(int level);
	HalfEdgeDS* m_pHalfEdgeDS;
	DownSampling* m_pDownSampling;
	std::vector<float> m_error;
};
}
}


#endif ARRANGE_POINT_HPP