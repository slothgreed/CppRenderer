#ifndef HALFEDGE_FACE_H
#define	HALFEDGE_FACE_H
namespace KI
{
namespace Topology
{
class HalfEdgeVertex;
class HalfEdge;

class DLL_EXPORT FaceAroundEdgeIterator : IIterator<HalfEdge*>
{
public:
	FaceAroundEdgeIterator(HalfEdgeFace* pFace);

	virtual bool HasNext();
	virtual void Next();
	virtual HalfEdge* Current();

private:
	HalfEdgeFace*	m_pFace;
	shared_ptr<HalfEdge> m_pEdgeItr;
	bool m_init; // èââÒÇ©Ç«Ç§Ç© next ÇåƒÇÒÇæÇÁ false
};

class DLL_EXPORT HalfEdgeFace : public IToString
{
public:
	HalfEdgeFace(int index);
	~HalfEdgeFace();

	void SetEdge(shared_ptr<HalfEdge> edge) { m_Edge = edge; };
	shared_ptr<HalfEdge> Edge() { return m_Edge; }

	int Index() { return m_Index; }

	virtual string ToString();
	void CalcElement();

	bool Intersection(const Ray& ray, vec3& position, float& distance);
	vec3 Gravity() { return m_gravity; }
	vec3 Centroid() { return m_centroid; }
	vec3 Normal() { return m_normal; }
	float Area() { return m_area; }
	void Validate();
	void GetVertex(vec3* v1, vec3* v2, vec3* v3);
private:

	vec3 CalcNormal();
	float CalcArea();
	vec3 CalcCentroid();
	int CalcVertexNum();
	void CalcGravity();

	shared_ptr<HalfEdge> m_Edge;
	int m_Index;
	
	vec3 m_gravity;
	vec3 m_centroid;
	float m_area;
	vec3 m_normal;

};
}
}
#endif // HALFEDGE_FACE_H