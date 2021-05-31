#ifndef HALFEDGE_OPERATOR
#define HALFEDGE_OPERATOR

namespace KI
{
namespace Topology
{
class HalfEdge;
class HalfEdgeDS;
class DLL_EXPORT HalfEdgeOperator
{
public:
	HalfEdgeOperator();
	~HalfEdgeOperator();

	void SmoothingByGravity(HalfEdgeDS* halfEdgeDS, int loopNum);
	void FaceSplit(HalfEdgeDS* halfEdgeDS, HalfEdgeFace* face, vec3 position);
	void EdgeSplit(HalfEdgeDS* halfEdgeDS, HalfEdge* edge, vec3 position);
	void EdgeFlips(HalfEdgeDS* halfEdgeDS, HalfEdge* edge);
	void SetRandomTangentForVertex(HalfEdgeDS* halfEdgeDS);
private:
	void MakeTriangle(HalfEdgeFace* face,
		HalfEdge* edge0,
		HalfEdge* edge1,
		HalfEdge* edge2,
		HalfEdge* oppo0,
		HalfEdge* oppo1,
		HalfEdge* oppo2);
};
}
}


#endif // !HALFEDGE_OPERATOR
