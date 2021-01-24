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

	void Calculate(int globalItrNum, int localItrNum);
	void LocalAlignment(int resolution);
	void GlobalAlignment();
private:
	void SetRandomTangent();
	void AssignLowerByUpper(int upperIndex);
	void ClosestDirection(
		vec3 tangent1, vec3 normal1, 
		vec3 tangent2, vec3 normal2,
		vec3* orient1, vec3* orient2);
	
	HalfEdgeDS* m_pHalfEdgeDS;
	DownSampling* m_pDownSampling;
	int m_locelItrNum;
};
}
}
#endif // !ALIGN_ORIENTATION_HPP
