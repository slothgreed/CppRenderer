#ifndef HALFEDGE_H
#define	 HALFEDGE_H
namespace KI
{
namespace Topology
{
class HalfEdgeVertex;
class HalfEdgeFace;
class DLL_EXPORT HalfEdge : public IToString
{
public:
	HalfEdge(int index);
	~HalfEdge();

	void Set(
		HalfEdgeVertex* end,
		HalfEdge* next,
		HalfEdge* before,
		HalfEdge* opposite,
		HalfEdgeFace* face );

	void SetEnd(HalfEdgeVertex* vertex);
	void SetNext(HalfEdge* end);
	void SetBefore(HalfEdge* end);
	void SetOpposite(HalfEdge* edge);
	void SetFace(HalfEdgeFace* face);

	HalfEdgeVertex* End() { return m_End; }
	HalfEdge* Next()		{ return m_Next; }
	HalfEdge* Before()	{ return m_Before; }
	HalfEdge* Opposite() { return m_Opposite; }
	HalfEdgeFace* Face() { return m_Face; }

	HalfEdgeVertex* Start() { return m_Opposite->End(); }

	virtual string ToString();

	void CalcElement();
	int Index() { return m_Index; }
	float Length() { return m_length; }
	float Angle() { return m_angle; }
	void Validate();
private:

	float CalcAngle();
	float CalcLength();
	HalfEdgeVertex* m_End;
	HalfEdge* m_Next;
	HalfEdge* m_Before;
	HalfEdge* m_Opposite;
	HalfEdgeFace* m_Face;
	int m_Index;
	float m_angle;
	float m_length;
};
}
}
#endif // HALFEDGE_H
