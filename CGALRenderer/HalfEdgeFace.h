#ifndef HALFEDGE_FACE_H
#define	HALFEDGE_FACE_H
namespace KI
{
class HalfEdgeVertex;
class HalfEdge;

class FaceAroundEdgeIterator : IIterator<shared_ptr<HalfEdge>>
{
public:
	FaceAroundEdgeIterator(HalfEdgeFace* pFace);

	virtual bool HasNext();
	virtual void Next();
	virtual shared_ptr<HalfEdge> Current();

private:
	HalfEdgeFace*	m_pFace;
	shared_ptr<HalfEdge> m_pEdgeItr;
	bool m_init; // èââÒÇ©Ç«Ç§Ç© next ÇåƒÇÒÇæÇÁ false
};

class HalfEdgeFace : public IToString
{
public:
	HalfEdgeFace(int index);
	~HalfEdgeFace();

	void SetEdge(shared_ptr<HalfEdge> edge) { m_Edge = edge; };
	shared_ptr<HalfEdge> Edge() { return m_Edge; }

	int Index() { return m_Index; }

	virtual string ToString();
	void CalcElement();

	bool Intersection(const vec3& direction, float& distance);
	vec3 Centroid() { return m_centroid; }
	vec3 Normal() { return m_normal; }
	float Area() { return m_area; }
private:

	vec3 CalcNormal();
	float CalcArea();
	vec3 CalcCentroid();
	

	shared_ptr<HalfEdge> m_Edge;
	int m_Index;

	vec3 m_centroid;
	float m_area;
	vec3 m_normal;

};


}
#endif // HALFEDGE_FACE_H