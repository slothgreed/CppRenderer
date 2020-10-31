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
		Logger::Output(LOG_LEVEL::LOG_LEVEL_ERROR, "file open error");
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

	//Normalize();
}

void HalfEdgeDS::CalcElement()
{

	// Edge Split Test
	//bool fix = true;
	//while (fix)
	//{
	//	fix = false;
	//	int size = m_EdgeList.size();
	//	vec3 position;
	//	HalfEdgeOperator operate;
	//	for (int i = 0; i < size; i++)
	//	{
	//		m_EdgeList[i]->CalcElement();
	//		if (m_EdgeList[i]->Length() > 2.5)
	//		{
	//			position = (m_EdgeList[i]->Start()->Position() + m_EdgeList[i]->End()->Position()) * 0.5f;
	//			operate.EdgeSplit(this, m_EdgeList[i], position);
	//			fix = true;
	//		}
	//	}
	//}

	// TODO : CalcElement がほかのものに依存する場合があるので順番を制御する必要がありそう。
	for (int i = 0; i < m_EdgeList.size(); i++)
	{
		m_EdgeList[i]->CalcElement();
		m_EdgeList[i]->Validate();
	}


	for (int i = 0; i < m_FaceList.size(); i++)
	{
		m_FaceList[i]->CalcElement();
		m_FaceList[i]->Validate();
	}

	for (int i = 0; i < m_VertexList.size(); i++)
	{
		m_VertexList[i]->CalcElement();
		m_VertexList[i]->Validate();
	}

	CalcEdgeParameter();
	CalcFaceParameter();

	// 隣接行列
	//AdjancyMatrix* pMatrix = new AdjancyMatrix(this);
	//delete pMatrix;

}

void HalfEdgeDS::CalcEdgeParameter()
{
	float edgeSum = 0;
	
	for (int i = 0; i < m_EdgeList.size(); i++)
	{
		edgeSum += m_EdgeList[i]->Length();
		m_maxEdgeLength =  std::max<float>(m_maxEdgeLength,m_EdgeList[i]->Length());
	}

	m_allEdgeLength = edgeSum;
	m_averageEdgeLength = edgeSum / m_EdgeList.size();
}

void HalfEdgeDS::CalcFaceParameter()
{
	float faceSum = 0;
	vec3 waitedCenter = vec3(0);
	for (int i = 0; i < m_FaceList.size(); i++)
	{
		faceSum += m_FaceList[i]->Area();
		waitedCenter += m_FaceList[i]->Area()* m_FaceList[i]->Gravity();
	}

	m_allSurfaceArea = faceSum;
	m_waitedCenter = waitedCenter / m_allSurfaceArea;
}

void HalfEdgeDS::Normalize()
{
	BDB bdb;
	for (int i = 0; i < m_VertexList.size(); i++)
	{
		bdb.Apply(m_VertexList[i]->Position());
	}

	float length = bdb.MaxEdgeLength();
	for (int i = 0; i < m_VertexList.size(); i++) 
	{
		vec3 position = m_VertexList[i]->Position();
		position += bdb.Min();
		position.x /= length;
		position.y /= length;
		position.z /= length;

		m_VertexList[i]->SetPosition(position);
	}
}

void HalfEdgeDS::AddVertex(shared_ptr<HalfEdgeVertex> pVertex)
{
	m_VertexList.push_back(pVertex);
}

void HalfEdgeDS::AddEdge(shared_ptr<HalfEdge> pEdge)
{
	m_EdgeList.push_back(pEdge);
}

void HalfEdgeDS::AddFace(shared_ptr<HalfEdgeFace> pFace)
{
	m_FaceList.push_back(pFace);
}

void HalfEdgeDS::RemoveVertex(int index)
{

}

void HalfEdgeDS::RemoveFace(int index)
{

}

void HalfEdgeDS::RemoveEdge(int index)
{

}
}
}