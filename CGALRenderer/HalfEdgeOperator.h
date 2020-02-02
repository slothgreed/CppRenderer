#ifndef HALFEDGE_OPERATOR
#define HALFEDGE_OPERATOR

namespace KI
{
class HalfEdge;
class HalfEdgeDS;
class HalfEdgeOperator
{
public:
	HalfEdgeOperator();
	~HalfEdgeOperator();

	void FaceSplit(HalfEdgeDS* halfEdgeDS, shared_ptr<HalfEdgeFace> face, vec3 position);

	void EdgeFlips(HalfEdgeDS* halfEdgeDS, shared_ptr<HalfEdge> edge);

private:

};

}


#endif // !HALFEDGE_OPERATOR
