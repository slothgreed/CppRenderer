#ifndef HALFEDGE_VERTEX_H
#define	 HALFEDGE_VERTEX_H
namespace KI
{
namespace Topology
{
class HalfEdge;
class DLL_EXPORT VertexAroundEdgeIterator : public IIterator<HalfEdge*>
{
public:
	VertexAroundEdgeIterator(HalfEdgeVertex* pVertex);

	virtual bool HasNext() override;
	virtual void Next() override;
	virtual HalfEdge* Current() override;

private:
	HalfEdgeVertex*	m_pVertex;
	HalfEdge* m_pEdgeItr;
	bool m_init; // èââÒÇ©Ç«Ç§Ç© next ÇåƒÇÒÇæÇÁ false

};
class DLL_EXPORT HalfEdgeVertex : public IToString
{
public:
	HalfEdgeVertex(int index);
	~HalfEdgeVertex();

	void SetEdge(shared_ptr<HalfEdge> edge) { m_Edge = edge; };

	shared_ptr<HalfEdge> Edge() { return m_Edge; }
	void SetPosition(vec3 position);
	void SetPosition(float x, float y, float z);
	vec3 Position() { return m_position; };
	int Index() { return m_Index; }

	virtual string ToString();
	void CalcElement();

	vec3 Normal() { return m_normal; }
	float Area() { return m_area; }
	bool Pick(const vec3& direction, float range, float& distance);
private:

	float CalcArea();
	vec3 CalcNormal();

	shared_ptr<HalfEdge> m_Edge;
	vec3 m_position;
	vec3 m_normal;
	float m_area;

	int m_Index;
};
}
}
#endif // HALFEDGE_VERTEX_H

