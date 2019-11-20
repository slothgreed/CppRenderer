#ifndef HALFEDGE_FACE_H
#define	HALFEDGE_FACE_H

class HalfEdgeVertex;
class HalfEdge;

class FaceAroundEdgeIterator : IIterator<HalfEdge*>
{
public:
	FaceAroundEdgeIterator(HalfEdgeFace* pFace);

	virtual bool HasNext();
	virtual void Next();
	virtual HalfEdge* Current();

private:
	HalfEdgeFace*	m_pFace;
	HalfEdge* m_pEdgeItr;
	bool m_init; // èââÒÇ©Ç«Ç§Ç© next ÇåƒÇÒÇæÇÁ false
};

class HalfEdgeFace : public IToString
{
public:
	HalfEdgeFace(int index);
	~HalfEdgeFace();

	vec3 Normal();
	void SetEdge(shared_ptr<HalfEdge> edge) { m_Edge = edge; };
	shared_ptr<HalfEdge> Edge() { return m_Edge; }

	int Index() { return m_Index; }

	virtual string ToString();
private:

	shared_ptr<HalfEdge> m_Edge;
	int m_Index;

};



#endif // HALFEDGE_FACE_H