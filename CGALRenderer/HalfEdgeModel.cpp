
HalfEdgeModel::HalfEdgeModel()
{
}

HalfEdgeModel::~HalfEdgeModel()
{
}


void HalfEdgeModel::Load(const string& filePath)
{
	if (FileUtility::CheckExtension(filePath, ".half") == false)
	{
		assert(0);
		return;
	}

	LoadInternal(filePath);
}

void HalfEdgeModel::LoadInternal(const string& filePath)
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
}

void HalfEdgeModel::GetFacetList(vector<vec3>& facetList, vector<vec3>& normalList)
{
	for (int i = 0; i < m_FaceList.size(); i++)
	{
		auto itr = FaceAroundEdgeIterator(m_FaceList[i].get());
		while (itr.HasNext()) 
		{
			facetList.push_back(
				itr.Current()->Start()->Position()
			);

			normalList.push_back(
				m_FaceList[i]->Normal()
			);

			itr.Next();
		}
	}
}

void HalfEdgeModel::GetEdgeList(vector<vec3>& edgeList)
{
	for (int i = 0; i < m_EdgeList.size(); i++)
	{
		edgeList.push_back(
			m_EdgeList[i]->Start()->Position()
		);

		edgeList.push_back(
			m_EdgeList[i]->End()->Position()
		);
	};
}

void HalfEdgeModel::GetVertexList(vector<vec3>& vertexList)
{
	for (int i = 0; i < m_EdgeList.size(); i++)
	{
		vertexList.push_back(
			m_VertexList[i]->Position()
		);
	}
}

void HalfEdgeModel::GetEdgeIndexList(vector<int>& index)
{
	for (int i = 0; i < m_EdgeList.size(); i++)
	{
		index.push_back(
			m_EdgeList[i]->Start()->Index()
		);

		index.push_back(
			m_EdgeList[i]->End()->Index()
		);
	};
}
void HalfEdgeModel::GetFaceIndexList(vector<int>& index)
{
	for (int i = 0; i < m_FaceList.size(); i++)
	{
		auto itr = FaceAroundEdgeIterator(m_FaceList[i].get());
		while (itr.HasNext())
		{
			index.push_back(
				itr.Current()->Start()->Index()
			);

			itr.Next();
		}
	}
}

void HalfEdgeModel::GetBDB(BDB& bdb)
{
	for (int i = 0; i < m_VertexList.size(); i++)
	{
		bdb.Apply(m_VertexList[i]->Position());
	}
}
