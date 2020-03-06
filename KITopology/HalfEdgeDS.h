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
	float CalcAllEdgeLength();

	const vector<shared_ptr<HalfEdge>>& EdgeList() { return m_EdgeList; }
	const vector<shared_ptr<HalfEdgeFace>>& FaceList() { return m_FaceList; }
	const vector<shared_ptr<HalfEdgeVertex>>& VertexList() { return m_VertexList; }

	void RemoveMesh(int index);
	void RemoveVertex(int index);
	void RemoveEdge(int index);
private:
	vector<shared_ptr<HalfEdge>> m_EdgeList;
	vector<shared_ptr<HalfEdgeFace>> m_FaceList;
	vector<shared_ptr<HalfEdgeVertex>> m_VertexList;

	float m_allEdgeLength;
};
}
}