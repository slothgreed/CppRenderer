
HalfEdgeModel::HalfEdgeModel()
{
}

HalfEdgeModel::~HalfEdgeModel()
{
}


void HalfEdgeModel::Load(const string& filePath)
{
	if (FileUtility::CheckExtension(filePath, "half") == false)
	{
		assert(0);
		return;
	}
}

void HalfEdgeModel::LoadInternal(const string& filePath)
{
	ifstream ifs(filePath);
	string line;
	if (ifs.fail())
	{
		Logger::Output(LOG_LEVEL::ERROR, "file open error");
		return;
	}

	while (getline(ifs, line))
	{

	}
}

void HalfEdgeModel::GetFacetList(vector<vec3>& facetList, vector<vec3>& normalList)
{

}

void HalfEdgeModel::GetEdgeList(vector<vec3>& edgeList)
{

}

void HalfEdgeModel::GetVertexList(vector<vec3>& vertexList)
{

}

void HalfEdgeModel::GetBDB(BDB& bdb)
{

}
