namespace KI
{

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

	m_HalfEdgeDS = make_shared<HalfEdgeDS>();
	m_HalfEdgeDS->Load(filePath);
	m_HalfEdgeDS->CalcElement();
}

void HalfEdgeModel::GetFacetList(vector<vec3>& facetList, vector<vec3>& normalList)
{
	auto halfFaceList = m_HalfEdgeDS->FaceList();
	for (int i = 0; i < halfFaceList.size(); i++)
	{
		auto itr = FaceAroundEdgeIterator(halfFaceList[i].get());
		while (itr.HasNext()) 
		{
			facetList.push_back(
				((HalfEdge*)itr.Current())->Start()->Position()
			);

			normalList.push_back(
				halfFaceList[i]->Normal()
			);

			itr.Next();
		}
	}
}

void HalfEdgeModel::GetEdgeList(vector<vec3>& edgeList)
{
	auto halfEdgeList = m_HalfEdgeDS->EdgeList();
	for (int i = 0; i < halfEdgeList.size(); i++)
	{
		edgeList.push_back(
			halfEdgeList[i]->Start()->Position()
		);

		edgeList.push_back(
			halfEdgeList[i]->End()->Position()
		);
	};
}

void HalfEdgeModel::GetPositionList(vector<vec3>& vertexList)
{
	auto halfVertexList = m_HalfEdgeDS->VertexList();
	for (int i = 0; i < halfVertexList.size(); i++)
	{
		vertexList.push_back(
			halfVertexList[i]->Position()
		);
	}
}

void HalfEdgeModel::GetEdgeIndexList(vector<int>& index)
{
	auto halfEdgeList = m_HalfEdgeDS->EdgeList();
	for (int i = 0; i < halfEdgeList.size(); i++)
	{
		index.push_back(
			halfEdgeList[i]->Start()->Index()
		);

		index.push_back(
			halfEdgeList[i]->End()->Index()
		);
	};
}
void HalfEdgeModel::GetFaceIndexList(vector<int>& index)
{
	auto halfFaceList = m_HalfEdgeDS->FaceList();
	for (int i = 0; i < halfFaceList.size(); i++)
	{
		auto itr = FaceAroundEdgeIterator(halfFaceList[i].get());
		while (itr.HasNext())
		{
			index.push_back(
				((HalfEdge*)itr.Current())->Start()->Index()
			);

			itr.Next();
		}
	}
}


void HalfEdgeModel::GetVertexList(vector<Vertex>& vertex)
{
	auto halfVertexList = m_HalfEdgeDS->VertexList();
	for (int i = 0; i < halfVertexList.size(); i++)
	{
		auto halfVertex = halfVertexList[i];
		vertex.push_back(
			Vertex(halfVertex->Position(),halfVertex->Normal())
		);
	}
}

void HalfEdgeModel::GetBDB(BDB& bdb)
{
	auto halfVertexList = m_HalfEdgeDS->VertexList();
	for (int i = 0; i < halfVertexList.size(); i++)
	{
		bdb.Apply(halfVertexList[i]->Position());
	}
}

float HalfEdgeModel::Intersection(const vec3& direction)
{
	auto halfFaceList = m_HalfEdgeDS->FaceList();
	float distance = numeric_limits<float>::infinity();
	for (int i = 0; i < halfFaceList.size(); i++)
	{
		auto face = halfFaceList[i];
		face->Intersection(direction, distance);
	}

	assert(0);
	return true;
}
}