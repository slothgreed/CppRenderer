#include "DownSampling.h"
namespace KI
{
namespace Topology
{

DownSampling::SampleData::SampleData(int positionNum)
	: m_Index(0),
	m_Position(vec3(0)),
	m_Normal(vec3(0)),
	m_Area(0)
{
}
DownSampling::SampleData::~SampleData()
{
}

void DownSampling::SampleData::Set(const vec3& position, const vec3& normal, float area)
{
	m_Position = position;
	m_Normal = normal;
	m_Area = area;
}

DownSampling::Resolution::Resolution()
{
}
DownSampling::Resolution::~Resolution()
{
	FreeData();
}

void DownSampling::Resolution::FreeData()
{
	RELEASE_INSTANCE(m_pMatrix);
	RELEASE_INSTANCE(m_toUpper);
	RELEASE_INSTANCE(m_toLower);
	RELEASE_ARRAY_INSTANCE(m_pSampleData, m_UpperNum);
}
void DownSampling::Resolution::NewData(int positionNum, int originalPosNum)
{
	m_UpperNum = positionNum;
	m_LowerNum = originalPosNum;
	m_toUpper = new ivec2[m_UpperNum];	// 子のインデックスを持つ
	m_toLower = new int[m_LowerNum];	// 親のインデックスを持つ
	m_pMatrix = new AdjancyMatrix();
}

ivec2 DownSampling::Resolution::GetToUpper(int index)
{
	assert(m_UpperNum > index);
	return m_toUpper[index];
}
int DownSampling::Resolution::GetToUpper(int index1, int index2)
{
	assert(m_UpperNum > index1);
	if (index2 == 0) {
		return m_toUpper[index1].x;
	}
	else {
		return m_toUpper[index1].y;
	}
}
void DownSampling::Resolution::SetToUpper(int index, int value1, int value2)
{
	m_toUpper[index].x = value1;
	m_toUpper[index].y = value2;
}
void DownSampling::Resolution::SetToLower(int index, int value)
{
	m_toLower[index] = value;
}

int DownSampling::Resolution::GetToLower(int index)
{
	return m_toLower[index];
}

DownSampling::SampleData* DownSampling::Resolution::GetData(int index)
{
	assert(m_UpperNum > index);
	return m_pSampleData[index];
}

AdjancyMatrix* DownSampling::Resolution::GetAdjancyMatrix()
{
	return m_pMatrix;
}
DownSampling::DownSampling(HalfEdgeDS* pHalfEdgeDS, int maxLevel)
	:m_pResolution(maxLevel),
	m_pHalfEdgeDS(pHalfEdgeDS),
	m_maxLevel(maxLevel)
{
	Generate();
}

void DownSampling::Generate()
{
	auto pOrgMatrix = make_shared<AdjancyMatrix>();
	auto pOrgResolution = make_shared<DownSampling::Resolution>();
	m_pResolution.push_back(pOrgResolution);
	for (int i = 1; i < m_maxLevel; i++)
	{
		auto pResolution = make_shared<DownSampling::Resolution>();
		m_pResolution.push_back(pResolution);

		CreateResolution(pOrgResolution, pResolution);
		pOrgResolution = pResolution;
	}

}


void DownSampling::CreateResolution(shared_ptr<DownSampling::Resolution> pOrgResolution,
	shared_ptr<DownSampling::Resolution> pResolution)
{
	struct Entry {
		int m_i, m_j;
		float m_order;
		Entry() {};
		Entry(int i, int j, float order)
			:m_i(i), m_j(j), m_order(order) {};
	};

	auto pOrgMatrix = pOrgResolution->GetAdjancyMatrix();
	auto vertexNum = pOrgMatrix->RowNum();
	Entry* entries = new Entry[vertexNum];

	auto vertexList = m_pHalfEdgeDS->VertexList();
	for (int i = 0; i < vertexNum; i++)
	{
		int startIndex = pOrgMatrix->Get(i, 0)->GetStart();
		for (int j = 0; j < pOrgMatrix->ColumnNum(i); j++)
		{
			int endIndex = pOrgMatrix->Get(i, j)->GetEnd();
			float nDot = glm::dot(vertexList[startIndex]->Normal(), vertexList[endIndex]->Normal());
			
			float area1 = vertexList[startIndex]->Area();
			float area2 = vertexList[endIndex]->Area();
			float ratio = area1 > area2 ? area1 / area2 : area2 / area1;
			entries[startIndex + endIndex] = Entry(i, j, nDot * ratio);
		}
	}

	vector<bool> mergeFlag(vertexNum, false);
	int newPositionNum = 0;
	for (int i = 0; i < vertexNum; i++)
	{
		const Entry &e = entries[i];
		if (mergeFlag[e.m_i] || mergeFlag[e.m_j]) {
			continue;
		}

		mergeFlag[e.m_i] = true;
		mergeFlag[e.m_j] = true;
		entries[newPositionNum] = entries[i];
		newPositionNum++;
	}

	pResolution->NewData(newPositionNum, vertexNum);
	for (int i = 0; i < newPositionNum; i++)
	{
		const Entry& entry = entries[i];
		auto vertex1 = vertexList[entry.m_i];
		auto vertex2 = vertexList[entry.m_j];
		float newArea = vertex1->Area() + vertex2->Area();
		vec3 pos1 = vertex1->Position();
		vec3 pos2 = vertex2->Position();

		vec3 newPosition = 
			(vertex1->Position() * vertex1->Area() + 
			 vertex2->Position() * vertex2->Area()) / newArea;
		vec3 newNormal =
			(vertex1->Normal() * vertex1->Area() +
			 vertex2->Normal() * vertex2->Area());
		newNormal = glm::normalize(newNormal);

		pResolution->SetToUpper(i, entry.m_i, entry.m_j);
		pResolution->SetToLower(entry.m_i, i);
		pResolution->SetToLower(entry.m_j, i);
		pResolution->GetData(i)->Set(newPosition, newNormal, newArea);
	}

	delete entries;

	//AdjancyMatrix* pMatrix = pResolution->GetAdjancyMatrix();
	//pMatrix->NewRow(newPositionNum);
	//// calculate neighborhood;
	//for (int i = 0; i < pResolution->GetClusterNum(); i++)
	//{
	//	vector<AdjancyMatrix::Link> newLink;
	//	for (int j = 0; j < pResolution->GetBranchNum(); j++)
	//	{
	//		int upper = pResolution->GetToUpper(i, j);
	//		int linkNum = pOrgMatrix->ColumnNum(upper);
	//		for (int lnkIdx = 0; lnkIdx < linkNum; lnkIdx++)
	//		{
	//			auto link = pOrgMatrix->Get(upper, lnkIdx);
	//			newLink.push_back(AdjancyMatrix::Link(
	//				pResolution->GetToLower(link->GetStart()),
	//				pResolution->GetToLower(link->GetEnd()), link->GetWeight()));
	//		}
	//	}

	//	std::sort(newLink.begin(), newLink.end());
	//	int id = -1;
	//	int size = 0;
	//	for (auto &link : newLink) {
	//		if (id != link.GetEnd() && link.GetEnd() != i) {
	//			id = link.GetEnd();
	//			size++;
	//		}
	//	}

	//	pMatrix->NewColumn(i, size);
	//	int k = 0;
	//	for (auto &link : newLink)
	//	{
	//		if (link.GetEnd() != i)
	//		{
	//			if (id != link.GetEnd())
	//			{
	//				pMatrix->Set(i, k, link);
	//				id = link.GetEnd();
	//				k++;
	//			}
	//			else
	//			{
	//				pMatrix->Get(i, k - 1)->SetWeight(pMatrix->Get(i, k - 1)->GetWeight() + link.GetWeight());
	//			}
	//		}
	//	}
	//}
}

shared_ptr<DownSampling::Resolution> DownSampling::GetResolution(int level)
{
	assert(level > m_pResolution.size());
	return m_pResolution[level];
}

void DownSampling::GetCluster(int level, std::vector<int>& index)
{
	index.resize(m_pHalfEdgeDS->VertexList().size());
	if (level == 0) {
		for (int i = 0; i < m_pHalfEdgeDS->VertexList().size(); i++) {
			index[i] = i;
		}
	}
	else
	{
		auto pCurrent = m_pResolution[level - 1];	// ex : 3
		for (int i = 0; i < pCurrent->GetClusterNum(); i++)
		{
			for (int j = 0; j < pCurrent->GetBranchNum(); i++)
			{
				int value = pCurrent->GetToUpper(i, j);
				GetClusterRecursive(level - 2, value, i, index);
			}
		}
	}
}

void DownSampling::GetClusterRecursive(int level, int parentClusterIndex, int clusterIndex, std::vector<int>& index)
{
	if (level == 0) {
		auto pCurrent = m_pResolution[level];
		for (int i = 0; i < index.size(); i++)
		{
			index[pCurrent->GetToLower(i)] = clusterIndex;
		}
	}
	else
	{
		auto pCurrent = m_pResolution[level - 1];	// ex : 1
		for (int i = 0; i < pCurrent->GetClusterNum(); i++)
		{
			for (int j = 0; j < pCurrent->GetBranchNum(); i++)
			{
				int value = pCurrent->GetToUpper(i, j);
				GetClusterRecursive(level - 2, value, i, index);
			}
		}
	}
}
DownSampling::~DownSampling()
{
}

}
}