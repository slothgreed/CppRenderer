#ifndef HALFEDGE_H
#define	 HALFEDGE_H
namespace KI
{
class HalfEdgeVertex;
class HalfEdgeFace;
class HalfEdge : public IToString
{
public:
	HalfEdge(int index);
	~HalfEdge();

	void Set(
		shared_ptr<HalfEdgeVertex> end,
		shared_ptr<HalfEdge> next,
		shared_ptr<HalfEdge> before,
		shared_ptr<HalfEdge> opposite,
		shared_ptr<HalfEdgeFace> face );

	void SetNext(shared_ptr<HalfEdge> end);
	void SetBefore(shared_ptr<HalfEdge> end);

	shared_ptr<HalfEdgeVertex> End() { return m_End; }
	shared_ptr<HalfEdge> Next()		{ return m_Next; }
	shared_ptr<HalfEdge> Before()	{ return m_Before; }
	shared_ptr<HalfEdge> Opposite() { return m_Opposite; }
	shared_ptr<HalfEdgeFace> Face() { return m_Face; }

	shared_ptr<HalfEdgeVertex> Start() { return m_Opposite->End(); }

	virtual string ToString();

	void CalcElement();
	int Index() { return m_Index; }
	float Length() { return m_length; }
	float Angle() { return m_angle; }
private:

	float CalcAngle();
	float CalcLength();
	shared_ptr<HalfEdgeVertex> m_End;
	shared_ptr<HalfEdge> m_Next;
	shared_ptr<HalfEdge> m_Before;
	shared_ptr<HalfEdge> m_Opposite;
	shared_ptr<HalfEdgeFace> m_Face;
	int m_Index;
	float m_angle;
	float m_length;
};

}
#endif // HALFEDGE_H
