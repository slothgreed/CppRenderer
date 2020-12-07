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
	void FaceSplit(HalfEdgeDS* halfEdgeDS, shared_ptr<HalfEdgeFace> face, vec3 position);
	void EdgeSplit(HalfEdgeDS* halfEdgeDS, shared_ptr<HalfEdge> edge, vec3 position);
	void EdgeFlips(HalfEdgeDS* halfEdgeDS, shared_ptr<HalfEdge> edge);
	void SetRandomTangentForVertex(HalfEdgeDS* halfEdgeDS);
private:
	void MakeTriangle(shared_ptr<HalfEdgeFace> face,
		shared_ptr<HalfEdge> edge0,
		shared_ptr<HalfEdge> edge1,
		shared_ptr<HalfEdge> edge2,
		shared_ptr<HalfEdge> oppo0,
		shared_ptr<HalfEdge> oppo1,
		shared_ptr<HalfEdge> oppo2);
};
}
}


#endif // !HALFEDGE_OPERATOR
