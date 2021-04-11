namespace KI
{
namespace Topology
{
void DownSamplingOperator::SetVertexOfCluster()
{
	assert(m_pInstance != nullptr);
	auto pResolution = m_pInstance->m_pResolution;
	auto pHalfEdgeDS = m_pInstance->m_pHalfEdgeDS;
	for (int level = 0; level < pResolution.size(); level++) {

		if (level == 0) {
			std::vector<DownSampling::SampleData> datas;
			datas.resize(pHalfEdgeDS->VertexList().size());
			for (int i = 0; i < pHalfEdgeDS->VertexList().size(); i++) {
				DownSampling::SampleData data(i);
				data.Set(i,
					pHalfEdgeDS->VertexList()[i]->Position(),
					pHalfEdgeDS->VertexList()[i]->Normal(),
					pHalfEdgeDS->VertexList()[i]->Area());
				datas.push_back(data);
			}
			pResolution[level]->GetData(0)->SetOriginal(datas);
		}
		else
		{
			auto pCurrent = pResolution[level];	// ex : 1
			if (pCurrent == NULL) {
				return;
			}
			for (int i = 0; i < pCurrent->GetClusterNum(); i++)
			{
				std::vector<DownSampling::SampleData> datas;
				for (int j = 0; j < pCurrent->GetBranchNum(); j++)
				{
					int _upper = pCurrent->GetToUpper(i, j);
					if (AdjancyMatrix::Link::INVALID == _upper)
						continue;
					SetVertexOfClusterRecursive(level - 1, _upper, &datas);
				}

				pCurrent->GetData(i)->SetOriginal(datas);
			}
		}
	}
}


void DownSamplingOperator::SetVertexOfClusterRecursive(int level, int upper, std::vector<DownSampling::SampleData>* datas)
{
	assert(m_pInstance != nullptr);
	auto pResolution = m_pInstance->m_pResolution;
	auto pHalfEdgeDS = m_pInstance->m_pHalfEdgeDS;
	if (level == 0) {
		assert(datas != nullptr);
		DownSampling::SampleData data(upper);
		data.Set(upper,
			pHalfEdgeDS->VertexList()[upper]->Position(),
			pHalfEdgeDS->VertexList()[upper]->Normal(),
			pHalfEdgeDS->VertexList()[upper]->Area());
		datas->push_back(data);
	}
	else
	{
		auto pCurrent = pResolution[level];	// ex : 0
		for (int j = 0; j < pCurrent->GetBranchNum(); j++)
		{
			int _upper = pCurrent->GetToUpper(upper, j);
			if (AdjancyMatrix::Link::INVALID == _upper)
				continue;
			SetVertexOfClusterRecursive(level - 1, _upper, datas);
		}
	}
}
void DownSamplingOperator::GetCluster(int level, std::vector<int>& index)
{
	assert(m_pInstance != nullptr);
	auto pResolution = m_pInstance->m_pResolution;
	auto pHalfEdgeDS = m_pInstance->m_pHalfEdgeDS;
	index.resize(pHalfEdgeDS->VertexList().size());
	if (level == pResolution.size()) {
		return;
	}
	if (level == 0) {
		for (int i = 0; i < pHalfEdgeDS->VertexList().size(); i++) {
			index[i] = i;
		}
	}
	else
	{
		auto pCurrent = pResolution[level];	// ex : 1
		if (pCurrent == NULL) {
			return;
		}
		int clusterIndex = 0;
		for (int i = 0; i < pCurrent->GetClusterNum(); i++)
		{
			for (int j = 0; j < pCurrent->GetBranchNum(); j++)
			{
				int _upper = pCurrent->GetToUpper(i, j);
				if (AdjancyMatrix::Link::INVALID == _upper)
					continue;
				GetClusterRecursive(level - 1, _upper, clusterIndex, index);
			}
			clusterIndex++;
		}
	}
}

void DownSamplingOperator::GetClusterRecursive(int level, int upper, int clusterIndex, std::vector<int>& index)
{
	assert(m_pInstance != nullptr);
	if (level == 0) {
		index[upper] = clusterIndex;
	}
	else
	{
		auto pCurrent = m_pInstance->m_pResolution[level];	// ex : 0
		for (int j = 0; j < pCurrent->GetBranchNum(); j++)
		{
			int _upper = pCurrent->GetToUpper(upper, j);
			if (AdjancyMatrix::Link::INVALID == _upper)
				continue;
			GetClusterRecursive(level - 1, _upper, clusterIndex, index);
		}
	}
}

void DownSamplingOperator::GetOriginalVertexTangent(int level, std::vector<vec3>* tangents)
{
	assert(m_pInstance != nullptr);
	assert(tangents != nullptr);
	assert(m_pInstance->GetResolutionNum() > level);
	auto pResolution = m_pInstance->GetResolution(level);
	auto pHalfEdgeDS = m_pInstance->m_pHalfEdgeDS;

	tangents->resize(pHalfEdgeDS->VertexList().size());
	for (int i = 0; i < pResolution->GetClusterNum(); i++)
	{
		auto pData = pResolution->GetData(i);
		for (int j = 0; j < pData->GetOriginalNum(); j++)
		{
			auto pOriginal = pData->GetOriginal(j);
			(*tangents)[pOriginal->Index()] = pOriginal->Tangent();
		}
	}
}
}
}
