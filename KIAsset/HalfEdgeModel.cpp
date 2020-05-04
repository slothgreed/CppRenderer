namespace KI
{
namespace Asset
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
	edgeList.resize(halfEdgeList.size() * 2);
	for (int i = 0; i < halfEdgeList.size(); i++)
	{
		edgeList[2 * i] = halfEdgeList[i]->Start()->Position();
		edgeList[2 * i+1] = halfEdgeList[i]->End()->Position();
	};
}

void HalfEdgeModel::GetPositionList(vector<vec3>& vertexList)
{
	auto halfVertexList = m_HalfEdgeDS->VertexList();
	vertexList.resize(halfVertexList.size());
	for (int i = 0; i < halfVertexList.size(); i++)
	{
		vertexList[i] = halfVertexList[i]->Position();
	}
}

void HalfEdgeModel::GetEdgeIndexList(vector<int>& index)
{
	auto halfEdgeList = m_HalfEdgeDS->EdgeList();
	index.resize(halfEdgeList.size() * 2);
	for (int i = 0; i < halfEdgeList.size(); i++)
	{
		index[2 * i] = halfEdgeList[i]->Start()->Index();
		index[2 * i + 1] = halfEdgeList[i]->End()->Index();
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
	vertex.resize(halfVertexList.size());
	for (int i = 0; i < halfVertexList.size(); i++)
	{
		auto halfVertex = halfVertexList[i];
		vertex[i] = Vertex(halfVertex->Position(),halfVertex->Normal());
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

void HalfEdgeModel::RaycastPick(RaycastPickInfo& pickInfo)
{
	auto halfFaceList = m_HalfEdgeDS->FaceList();
	vec3 position;
	
	if (pickInfo.Type() & PICK_TYPE::PICK_TYPE_FACE)
	{
		for (int i = 0; i < halfFaceList.size(); i++)
		{
			auto face = halfFaceList[i];
			float distance = numeric_limits<float>::infinity();
			if (face->Intersection(pickInfo.GetRay(), position, distance))
			{
				if (pickInfo.MinDistance() > distance)
				{
					pickInfo.SetResult(PICK_TYPE::PICK_TYPE_FACE, "HalfEdgeModel", 3 * i, 3, distance);
				}
			}
		}

	}
}


}
}