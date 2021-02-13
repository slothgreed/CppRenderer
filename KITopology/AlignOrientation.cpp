namespace KI
{
namespace Topology
{
AlignOrientation::AlignOrientation(HalfEdgeDS* pHalfEdgeDS, DownSampling* pDownSampling)
{
	m_pHalfEdgeDS = pHalfEdgeDS;
	m_pDownSampling = pDownSampling;
	SetRandomTangent();
}

AlignOrientation::~AlignOrientation()
{
}

void AlignOrientation::ClosestDirection(const vec3& tangent1, const vec3& normal1,
										const vec3& tangent2, const vec3& normal2,
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
			if (maxInner < inner) {
				max1 = i;
				max2 = j;
				maxInner = inner;
			}
		}
	}

	maxInner = glm::dot(orients1[max1], orients2[max2]);
	assert(maxInner < 1.5);

	*orient1 = orients1[max1];
	if (maxInner > 0) {
		*orient2 = orients2[max2];
	}
	else {
		*orient2 = -orients2[max2];
	}
}

void AlignOrientation::AssignLowerByUpper(int upperIndex)
{
	// upper‚ðŠî‚É1ŠK‘w‰º(×‚©‚¢)‚Ì‚à‚Ì‚É”½‰f‚·‚éB
	int upperLevel = upperIndex;
	int lowerLevel = upperIndex + 1;
	auto pResolution = m_pDownSampling->GetResolution(upperLevel);

	for (int j = 0; j < pResolution->GetClusterNum(); j++)
	{
		for (int k = 0; k < pResolution->GetBranchNum(); k++)
		{
			auto pVertexIndex = pResolution->GetToUpper(j, k);
			if (pVertexIndex == AdjancyMatrix::Link::INVALID) {
				continue;
			}

			//auto pVertex = pVertexIndex[pLink1->GetStart()];
			//vec3 tangent = pVertex->Tangent();
			//vec3 normal = pVertexList[pVertexIndex]->Normal();
			//pVertex->SetTangent(glm::normalize(pVertex->Tangent() - normal * glm::dot(normal, tangent)));
		}
	}

}

void AlignOrientation::SetRandomTangent()
{
	for (int i = 0; i < m_pHalfEdgeDS->VertexList().size(); i++)
	{
		auto pVertex = m_pHalfEdgeDS->VertexList()[i];

		vec3 end = pVertex->Edge()->End()->Position();
		vec3 vector = end - pVertex->Position();
		// By. Discrete Differential-Geometry Operators for Triangulated 2 - Manifolds 5 - 3, dij
		vec3 tangent = vector - pVertex->Normal() * glm::dot(vector, pVertex->Normal());
		tangent = glm::normalize(tangent);
		m_pHalfEdgeDS->VertexList()[i]->SetTangent(tangent);
	}
}
void AlignOrientation::Calculate(int globalItrNum, int localItrNum)
{
	assert(m_pDownSampling != NULL);

	int resolutionIndex = m_pDownSampling->GetResolutionNum() - 1;
	for (int i = 0; i < globalItrNum; i++)
	{
		for (int j = 0; j < localItrNum; j++)
		{
			LocalAlignment(resolutionIndex);
		}

		int globalItr = resolutionIndex;
		while (globalItr != 0)
		{
			AssignLowerByUpper(globalItr);
			globalItr--;
		}

		CalcErrorValue();

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

			assert(weight != 0.0f && pLink2->GetWeight() != 0.0f);	// tangent‚Ì’·‚³‚ª0‚É‚È‚éB
			tangent = glm::normalize(tangent);
		}

		if (weight > 0) {
			pVertex1->SetTangent(tangent);
		}
	}

}

void AlignOrientation::CalcErrorValue()
{
	assert(m_pHalfEdgeDS != nullptr);
	auto pVertexs = m_pHalfEdgeDS->VertexList();
	float sum = 0;
	for (int i = 0; i < pVertexs.size(); i++)
	{
		VertexAroundEdgeIterator itr(pVertexs[i].get());
		for (; itr.HasNext(); itr.Next())
		{
			auto pEdge1 = itr.Current();
			auto pEdge2 = itr.CurrentNext();

			vec3 orient1, orient2;
			ClosestDirection(
				pEdge1->End()->Tangent(), pEdge1->End()->Normal(),
				pEdge2->End()->Tangent(), pEdge2->End()->Normal(),
				&orient1, &orient2);

			float inner = glm::dot(orient1, orient2);
			assert(inner < 2);
			float angle = 0;
			if (inner > 1) {
				inner = 1;
			} 
			
			angle = MathHelper::ToAngle(std::acos(inner));
			sum += angle * angle;
		}
	}

	m_error.push_back(sum);
}
}
}


