#ifndef ALIGN_ORIENTATION_HPP
#define ALIGN_ORIENTATION_HPP

namespace KI
{
namespace Topology
{
class AlignOrientation
{
public:
	AlignOrientation(HalfEdgeDS* pHalfEdgeDS);
	~AlignOrientation();

	void Calculate(int globalItrNum, int localItrNum);
	void LocalAlignment(int resolution);
	void GlobalAlignment();
private:
	void AssignLowerByUpper(int resolutionIndex);
	void ClosestDirection(
		vec3 tangent1, vec3 normal1, 
		vec3 tangent2, vec3 normal2,
		vec3* orient1, vec3* orient2);
	
	HalfEdgeDS* m_pHalfEdgeDS;
	int m_locelItrNum;
};
}
}
#endif // !ALIGN_ORIENTATION_HPP
