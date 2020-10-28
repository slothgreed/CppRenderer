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

	const vector<shared_ptr<HalfEdge>>& EdgeList() { return m_EdgeList; }
	const vector<shared_ptr<HalfEdgeFace>>& FaceList() { return m_FaceList; }
	const vector<shared_ptr<HalfEdgeVertex>>& VertexList() { return m_VertexList; }

	void AddVertex(shared_ptr<HalfEdgeVertex> pVertex);
	void AddEdge(shared_ptr<HalfEdge> pVertex);
	void AddFace(shared_ptr<HalfEdgeFace> pVertex);

	void RemoveVertex(int index);
	void RemoveEdge(int index);
	void RemoveFace(int index);

	void Normalize();
private:
	vector<shared_ptr<HalfEdge>> m_EdgeList;
	vector<shared_ptr<HalfEdgeFace>> m_FaceList;
	vector<shared_ptr<HalfEdgeVertex>> m_VertexList;

	float m_averageEdgeLength;
	float m_allEdgeLength;
	float m_maxEdgeLength;
	float m_allSurfaceArea;
	vec3 m_waitedCenter;
};
}
}