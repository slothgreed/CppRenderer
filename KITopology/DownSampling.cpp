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

void DownSampling::SampleData::Set(int index, const vec3& position, const vec3& normal, float area)
{
	m_Index = index;
	m_Position = position;
	m_Normal = normal;
	m_Area = area;
}

DownSampling::Resolution::Resolution()
	:m_toUpper(NULL),
	m_UpperNum(0),
	m_toLower(NULL),
	m_LowerNum(0)
{
}
DownSampling::Resolution::~Resolution()
{
	FreeData();
}

void DownSampling::Resolution::FreeData()
{
	m_toUpper.clear();
	m_toLower.clear();
	m_pSampleData.clear();
}
void DownSampling::Resolution::NewData(int positionNum, int originalPosNum)
{
	m_UpperNum = positionNum;
	m_LowerNum = originalPosNum;
	m_toUpper.resize(m_UpperNum);	// 子のインデックスを持つ
	m_toLower.resize(m_LowerNum);	// 親のインデックスを持つ
	m_pSampleData.resize(positionNum);
	m_pMatrix = make_shared<AdjancyMatrix>();
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
	assert(m_toLower.size() != 0);
	m_toLower[index] = value;
}

int DownSampling::Resolution::GetToLower(int index)
{
	return m_toLower[index];
}

DownSampling::SampleData* DownSampling::Resolution::GetData(int index)
{
	assert(m_UpperNum > index);
	return &m_pSampleData[index];
}


DownSampling::DownSampling(HalfEdgeDS* pHalfEdgeDS)
	:m_pResolution(0),
	m_pHalfEdgeDS(pHalfEdgeDS)
{
	Generate();
}

void DownSampling::InitialResolution(shared_ptr<DownSampling::Resolution> pResolution, HalfEdgeDS* pHalfEdgeDS)
{
	pResolution->NewData(pHalfEdgeDS->VertexList().size(), 0);
	for (int i = 0; i < pResolution->GetClusterNum(); i++)
	{
		auto pVertex = pHalfEdgeDS->VertexList()[i];
		pResolution->GetData(i)->Set(i, pVertex->Position(),pVertex->Normal(),pVertex->Area());
	}

	pResolution->SetAdjancyMatrix(make_shared<HalfEdgeAdjancyMatrix>(m_pHalfEdgeDS));

}
void DownSampling::Generate()
{
	auto pOrgMatrix = make_shared<AdjancyMatrix>();
	auto pOrgResolution = make_shared<DownSampling::Resolution>();
	InitialResolution(pOrgResolution, m_pHalfEdgeDS);
	m_pResolution.push_back(pOrgResolution);
	int i = 1;
	// 大体の数これ以上になるなら評価方法を変えたほうが良い
	int maybeNum = std::log2(m_pHalfEdgeDS->VertexList().size()) * 2;
	while (true)
	{
		auto pResolution = make_shared<DownSampling::Resolution>();
		m_pResolution.push_back(pResolution);

		CreateResolution(i, pOrgResolution, pResolution);
		pOrgResolution = pResolution;
		if (pResolution->GetAdjancyMatrix()->Size() == 0) {
			break;
		}

		i++;

		//AdjancyMatrixCSVIO val;
		//val.Output("C:\\Users\\stmnd\\Desktop\\Adjancy\\test" + std::to_string(i) + ".txt", pOrgResolution->GetAdjancyMatrix().get());
		if (maybeNum == i) {
			assert(0);
		}
	}
}


void DownSampling::CreateResolution(int level,
	shared_ptr<DownSampling::Resolution> pOrgResolution,
	shared_ptr<DownSampling::Resolution> pResolution)
{
	struct Entry {
		int m_i, m_j;
		float m_order;
		Entry() {};
		Entry(int i, int j, float order)
			:m_i(i), m_j(j), m_order(order) {};
		inline bool operator<(const Entry& entry) const { return m_order < entry.m_order; };
	};

	auto pOrgMatrix = pOrgResolution->GetAdjancyMatrix();
	auto vertexNum = pOrgMatrix->RowNum();
	std::vector<Entry> entries(pOrgMatrix->Size());

	int counter = 0;
	for (int i = 0; i < vertexNum; i++)
	{
		int startIndex = pOrgMatrix->Get(i, 0)->GetStart();
		vec3 normal1 = pOrgResolution->GetData(startIndex)->Normal();
		float area1 = pOrgResolution->GetData(startIndex)->Area();

		for (int j = 0; j < pOrgMatrix->ColumnNum(i); j++)
		{
			int endIndex = pOrgMatrix->Get(i, j)->GetEnd();
			vec3 normal2 = pOrgResolution->GetData(endIndex)->Normal();
			float area2 = pOrgResolution->GetData(endIndex)->Area();
			
			float nDot = std::abs(glm::dot(normal1, normal2));
			float ratio = area1 + area2; //? area1 / area2 : area2 / area1;
			assert(startIndex + endIndex < pOrgMatrix->Size());
			entries[counter] = Entry(startIndex, endIndex, nDot * ratio);
			counter++;
		}
	}

	std::sort(entries.begin(), entries.end());
	//FileWriter writer;
	//writer.Open("C:\\Users\\stmnd\\Desktop\\Adjancy\\Area\\Area" + std::to_string(level) + ".txt");
	//for (int i = 0; i < entries.size(); i++) {
	//	writer.Write("(" + std::to_string(entries[i].m_i) + "," + std::to_string(entries[i].m_j) + "," + std::to_string(entries[i].m_order) + ")", true);
	//}
	//writer.Write("", true);
	//writer.Close();
	vector<bool> mergeFlag(vertexNum, false);
	int collapseNum = 0;
	for (int i = 0; i < entries.size(); i++)
	{
		const Entry &e = entries[i];
		if (mergeFlag[e.m_i] || mergeFlag[e.m_j]) {
			continue;
		}

		mergeFlag[e.m_i] = true;
		mergeFlag[e.m_j] = true;
		entries[collapseNum] = entries[i];
		collapseNum++;
	}

	int clusterNum = vertexNum - collapseNum;
	pResolution->NewData(clusterNum, vertexNum);
	for (int i = 0; i < collapseNum; i++)
	{
		const Entry& entry = entries[i];
		auto data1 = pOrgResolution->GetData(entry.m_i);
		auto data2 = pOrgResolution->GetData(entry.m_j);
		float newArea = data1->Area() + data2->Area();
		vec3 pos1 = data1->Position();
		vec3 pos2 = data2->Position();

		vec3 newPosition = 
			(data1->Position() * data1->Area() +
			 data2->Position() * data2->Area()) / newArea;
		vec3 newNormal =
			(data1->Normal() * data1->Area() +
			 data2->Normal() * data2->Area());
		newNormal = glm::normalize(newNormal);

		pResolution->SetToUpper(i, entry.m_i, entry.m_j);
		pResolution->SetToLower(entry.m_i, i);
		pResolution->SetToLower(entry.m_j, i);
		pResolution->GetData(i)->Set(i, newPosition, newNormal, newArea);
	}

	// merge していないもの
	int isolateIndex = collapseNum;
	for (int i = 0; i < vertexNum; i++)
	{
		if (!mergeFlag[i]) {
			// 上位の者そのままセットする。
			auto data = pOrgResolution->GetData(i);
			pResolution->GetData(isolateIndex)->Set(isolateIndex, data->Position(), data->Normal(), data->Area());
			pResolution->SetToUpper(isolateIndex, i, AdjancyMatrix::Link::INVALID);
			pResolution->SetToLower(i,isolateIndex);
			isolateIndex++;
		}
	}



	auto pMatrix = pResolution->GetAdjancyMatrix();

	if (clusterNum == 1) {
		// cluster が 1個の場合は隣接行列を作らない。
		return;
	}

	pMatrix->NewRow(clusterNum);
	// calculate neighborhood;
	for (int i = 0; i < pResolution->GetClusterNum(); i++)
	{
		vector<AdjancyMatrix::Link> newLink;
		for (int j = 0; j < pResolution->GetBranchNum(); j++)
		{
			int upper = pResolution->GetToUpper(i, j);
			if (upper == AdjancyMatrix::Link::INVALID) {
				continue;
			}
			int linkNum = pOrgMatrix->ColumnNum(upper);
			for (int lnkIdx = 0; lnkIdx < linkNum; lnkIdx++)
			{
				auto link = pOrgMatrix->Get(upper, lnkIdx);
				newLink.push_back(AdjancyMatrix::Link(
					pResolution->GetToLower(link->GetStart()),
					pResolution->GetToLower(link->GetEnd()), link->GetWeight()));
			}
		}

		std::sort(newLink.begin(), newLink.end());
		int vertexId = -1;
		int size = 0;
		for (auto &link : newLink) {
			if (vertexId != link.GetEnd() && link.GetEnd() != i) {
				vertexId = link.GetEnd();
				size++;
			}
		}

		pMatrix->NewColumn(i, size);
		int k = 0;
		vertexId = -1;
		for (auto &link : newLink)
		{
			if (link.GetEnd() != i)
			{
				if (vertexId != link.GetEnd())
				{
					pMatrix->Set(i, k, link);
					vertexId = link.GetEnd();
					k++;
				}
				else
				{
					pMatrix->Get(i, k - 1)->SetWeight(pMatrix->Get(i, k - 1)->GetWeight() + link.GetWeight());
				}
			}
		}
	}
}

shared_ptr<DownSampling::Resolution> DownSampling::GetResolution(int level)
{
	assert(level < m_pResolution.size());
	return m_pResolution[level];
}

void DownSampling::GetCluster(int level, std::vector<int>& index)
{
	index.resize(m_pHalfEdgeDS->VertexList().size());
	if (level == m_pResolution.size()) {
		return;
	}
	if (level == 0) {
		for (int i = 0; i < m_pHalfEdgeDS->VertexList().size(); i++) {
			index[i] = i;
		}
	}
	else
	{
		auto pCurrent = m_pResolution[level];	// ex : 3
		if (pCurrent == NULL) {
			return;
		}
		int clusterIndex = 0;
		for (int i = 0; i < pCurrent->GetClusterNum(); i++)
		{
			for (int j = 0; j < pCurrent->GetBranchNum(); j++)
			{
				int value = pCurrent->GetToUpper(i, j);
				if (AdjancyMatrix::Link::INVALID == value)
					continue;
				GetClusterRecursive(level-1, 0, value, clusterIndex, index);
				clusterIndex++;
			}
		}
	}
}

void DownSampling::GetClusterRecursive(int level, int targetLevel, int upper, int clusterIndex, std::vector<int>& index)
{
	if (level == 0) {
		auto pCurrent = m_pResolution[level];
		index[upper] = clusterIndex;
	}
	else
	{
		auto pCurrent = m_pResolution[level];	// ex : 1
		//for (int i = 0; i < pCurrent->GetClusterNum(); i++)
		{
			for (int j = 0; j < pCurrent->GetBranchNum(); j++)
			{
				int value = pCurrent->GetToUpper(upper, j);
				if (AdjancyMatrix::Link::INVALID == value)
					continue;
				GetClusterRecursive(level - 1, targetLevel, value, clusterIndex, index);
			}
		}
	}
}

}
}