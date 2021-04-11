#ifndef ALIGN_ORIENTATION_HPP
#define ALIGN_ORIENTATION_HPP

namespace KI
{
namespace Topology
{
class DLL_EXPORT AlignOrientation
{
public:
	AlignOrientation(HalfEdgeDS* pHalfEdgeDS, DownSampling* pDownSampling);
	~AlignOrientation();
	const std::vector<float>& ErrorValue() { return m_error; }
	void Calculate(int localItrNum);
	void CalculateLocal_Debug(int level, int localItrNum);

	void LocalAlignment(int resolution);
private:
	void InitRandomTangent();
	void AssignLowerByUpper(int upperIndex);
	void ClosestDirection(
		const vec3& tangent1, const vec3& normal1,
		const vec3& tangent2, const vec3& normal2,
		vec3* orient1, vec3* orient2);
	void CalcErrorValue();

	HalfEdgeDS* m_pHalfEdgeDS;
	DownSampling* m_pDownSampling;
	int m_locelItrNum;
	std::vector<float> m_error;

};
}
}
#endif // !ALIGN_ORIENTATION_HPP
