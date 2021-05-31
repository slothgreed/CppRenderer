namespace KI
{
namespace Topology
{
class DLL_EXPORT HalfEdgeDS
{
public:
	HalfEdgeDS();
	~HalfEdgeDS();

	void Load(const string& filePath);
	void CalcElement();
	void CalcEdgeParameter();
	void CalcFaceParameter();

	const vector<HalfEdge*>& EdgeList() { return m_EdgeList; }
	const vector<HalfEdgeFace*>& FaceList() { return m_FaceList; }
	const vector<HalfEdgeVertex*>& VertexList() { return m_VertexList; }

	void AddVertex(HalfEdgeVertex* pVertex);
	void AddEdge(HalfEdge* pVertex);
	void AddFace(HalfEdgeFace* pVertex);

	void RemoveVertex(int index);
	void RemoveEdge(int index);
	void RemoveFace(int index);

	void Normalize();
private:
	vector<HalfEdge*> m_EdgeList;
	vector<HalfEdgeFace*> m_FaceList;
	vector<HalfEdgeVertex*> m_VertexList;

	float m_averageEdgeLength;
	float m_allEdgeLength;
	float m_maxEdgeLength;
	float m_allSurfaceArea;
	vec3 m_waitedCenter;
};
}
}