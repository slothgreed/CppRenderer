namespace KI
{
namespace Topology
{
HalfEdgeDS::HalfEdgeDS()
{
}

HalfEdgeDS::~HalfEdgeDS()
{
}

void HalfEdgeDS::Load(const string& filePath)
{
	ifstream binaryStream(filePath, ios::in | ios::binary);
	if (!binaryStream)
	{
		Logger::Output(LOG_LEVEL::ERROR, "file open error");
		return;
	}

	int version = 0;
	int vertexSize = 0;
	int edgeSize = 0;
	int faceSize = 0;

	binaryStream.read((char*)&version, sizeof(int));
	binaryStream.read((char*)&vertexSize, sizeof(int));
	binaryStream.read((char*)&edgeSize, sizeof(int));
	binaryStream.read((char*)&faceSize, sizeof(int));

	if (version != 2 ||
		vertexSize == 0 ||
		edgeSize == 0 ||
		faceSize == 0)
	{
		assert(0);
	}

	m_VertexList.resize(vertexSize);
	for (int i = 0; i < vertexSize; i++)
	{
		m_VertexList[i] = make_shared<HalfEdgeVertex>(i);
	}

	m_EdgeList.resize(edgeSize);
	for (int i = 0; i < edgeSize; i++)
	{
		m_EdgeList[i] = make_shared<HalfEdge>(i);
	}

	m_FaceList.resize(faceSize);
	for (int i = 0; i < faceSize; i++)
	{
		m_FaceList[i] = make_shared<HalfEdgeFace>(i);
	}

	float x = 0, y = 0, z = 0;
	int edge = 0;
	for (int i = 0; i < vertexSize; i++)
	{
		binaryStream.read((char*)&x, sizeof(float));
		binaryStream.read((char*)&y, sizeof(float));
		binaryStream.read((char*)&z, sizeof(float));
		binaryStream.read((char*)&edge, sizeof(int));
		m_VertexList[i]->SetPosition(x, y, z);
		m_VertexList[i]->SetEdge(
			m_EdgeList[edge]
		);
	}

	int end = 0, next = 0, before = 0, opposite = 0, face = 0;
	for (int i = 0; i < edgeSize; i++)
	{
		binaryStream.read((char*)&end, sizeof(int));
		binaryStream.read((char*)&next, sizeof(int));
		binaryStream.read((char*)&before, sizeof(int));
		binaryStream.read((char*)&opposite, sizeof(int));
		binaryStream.read((char*)&face, sizeof(int));
		m_EdgeList[i]->Set(
			m_VertexList[end],
			m_EdgeList[next],
			m_EdgeList[before],
			m_EdgeList[opposite],
			m_FaceList[face]
		);
	}

	for (int i = 0; i < faceSize; i++)
	{
		binaryStream.read((char*)&edge, sizeof(int));
		m_FaceList[i]->SetEdge(
			m_EdgeList[edge]
		);
	}

	binaryStream.close();

	//HalfEdgeOperator halfEdgeOperator;
	//for (int i = 0; i < m_EdgeList.size(); i++)
	//{
	//	halfEdgeOperator.EdgeFlips(this, m_EdgeList[i]);
	//}
}

void HalfEdgeDS::CalcElement()
{
	// TODO : CalcElement ‚ª‚Ù‚©‚Ì‚à‚Ì‚ÉˆË‘¶‚·‚éê‡‚ª‚ ‚é‚Ì‚Å‡”Ô‚ð§Œä‚·‚é•K—v‚ª‚ ‚è‚»‚¤B

	for (int i = 0; i < m_EdgeList.size(); i++)
	{
		m_EdgeList[i]->CalcElement();
	}

	for (int i = 0; i < m_FaceList.size(); i++)
	{
		m_FaceList[i]->CalcElement();
	}

	for (int i = 0; i < m_VertexList.size(); i++)
	{
		m_VertexList[i]->CalcElement();
	}

	m_allEdgeLength = CalcAllEdgeLength();
}

float HalfEdgeDS::CalcAllEdgeLength()
{
	float edgeSum = 0;
	for (int i = 0; i < m_EdgeList.size(); i++)
	{
		edgeSum += m_EdgeList[i]->Length();
	}

	return edgeSum / 2; // opposite ‚Ì‚à‚Ì‚àŠÜ‚Ü‚ê‚Ä‚¢‚é‚Ì‚Å/2
}

void HalfEdgeDS::RemoveVertex(int index)
{

}

void HalfEdgeDS::RemoveMesh(int index)
{

}

void HalfEdgeDS::RemoveEdge(int index)
{

}
}
}