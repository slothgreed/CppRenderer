namespace KI
{
namespace Topology
{
AlignOrientation::AlignOrientation(HalfEdgeDS* pHalfEdgeDS, DownSampling* pDownSampling)
{
	m_pHalfEdgeDS = pHalfEdgeDS;
	m_pDownSampling = pDownSampling;
}

AlignOrientation::~AlignOrientation()
{
}

void AlignOrientation::ClosestDirection(vec3 tangent1, vec3 normal1,
										vec3 tangent2, vec3 normal2,
										vec3* orient1, vec3* orient2)
{
	vec3 orients1[2] = { tangent1, glm::cross(tangent1,normal1) };
	vec3 orients2[2] = { tangent1, glm::cross(tangent2,normal2) };

	float maxInner = -0.0f;
	int max1 = -1;
	int max2 = -1;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			float inner = std::abs(glm::dot(orients1[i], orients2[j]));
			if (maxInner > inner) {
				max1 = i;
				max2 = j;
				maxInner = inner;
			}
		}
	}

	maxInner = glm::dot(orients1[max1], orients2[max2]);

	*orient1 = orients1[max1];
	if (maxInner > 0) {
		*orient2 = orients2[max2];
	}
	else
	{
		*orient2 = -orients2[max2];
	}
}

void AlignOrientation::AssignLowerByUpper(int upperIndex)
{
	// upper‚ðŠî‚É1ŠK‘w‰º(×‚©‚¢)‚Ì‚à‚Ì‚É”½‰f‚·‚éB
	int upperLevel = upperIndex;
	int lowerLevel = upperIndex + 1;
	auto pResolution = m_pDownSampling->GetResolution(upperLevel);
	auto pVertexList = m_pHalfEdgeDS->VertexList();

	auto pAdjancyMatrix = pResolution->GetAdjancyMatrix();

	for (int i = 0; i < pAdjancyMatrix->RowNum(); i++)
	{
		auto pLink1 = pAdjancyMatrix->Get(i, 0);
		for (int j = 0; j < pResolution->GetDataNum(); j++)
		{
			for (int k = 0; k < 2; k++)
			{
				auto pVertexIndex = pResolution->GetUpper(pLink1->GetEnd(), k);
				auto pVertex = pVertexList[pLink1->GetStart()];
				vec3 tangent = pVertex->Tangent();
				vec3 normal = pVertexList[pVertexIndex]->Normal();
				pVertex->SetTangent(pVertex->Tangent() - normal * glm::dot(normal, tangent));
			}
		}
	}
}
void AlignOrientation::Calculate(int globalItrNum, int localItrNum)
{
	assert(m_pDownSampling != NULL);

	int resolutionIndex = m_pDownSampling->GetResolutionNum() - 1;
	for (int i = 0; i < globalItrNum; i++)
	{
		
		for (int j = localItrNum; j < localItrNum; j++)
		{
			LocalAlignment(resolutionIndex);
		}

		AssignLowerByUpper(resolutionIndex);

		resolutionIndex--;
	}
}

void AlignOrientation::LocalAlignment(int resolution)
{
	auto pResolution = m_pDownSampling->GetResolution(resolution);
	auto pAdjancyMatrix = pResolution->GetAdjancyMatrix();
	auto pVertexList = m_pHalfEdgeDS->VertexList();
	vec3 orient1;
	vec3 orient2;
	for (int i = 0; i < pAdjancyMatrix->RowNum(); i++)
	{
		auto pLink1 = pAdjancyMatrix->Get(i, 0);
		int vertexIndex1 = pLink1->GetStart();
		auto pVertex1 = pVertexList[vertexIndex1];
		
		float weight = 0.0f;
		vec3 tangent = pVertex1->Tangent();
		for (int j = 0; j < pAdjancyMatrix->ColumnNum(i); j++)
		{
			auto pLink2 = pAdjancyMatrix->Get(i, j);
			int vertexIndex2 = pLink2->GetEnd();
			auto pVertex2 = pVertexList[vertexIndex2];

			ClosestDirection(
				tangent, pVertex1->Normal(),
				pVertex2->Tangent(), pVertex2->Normal(),
				&orient1, &orient2);
			
			tangent = orient1 * weight + orient2 * pLink2->GetWeight();
			tangent = tangent - pVertex1->Normal() * glm::dot(pVertex1->Normal(), tangent);
			weight += pLink2->GetWeight();

			tangent = glm::normalize(tangent);
		}

		if (weight > 0) {
			pVertex1->SetTangent(tangent);
		}

	}

}

void AlignOrientation::GlobalAlignment()
{

}
}
}


