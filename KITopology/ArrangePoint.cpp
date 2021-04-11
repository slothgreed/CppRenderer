
namespace KI
{
namespace Topology
{
ArrangePoint::ArrangePoint(HalfEdgeDS* pHalfEdgeDS, DownSampling* pDownSampling)
	:m_pHalfEdgeDS(pHalfEdgeDS),
	m_pDownSampling(pDownSampling)
{
}

ArrangePoint::~ArrangePoint()
{
}

void ArrangePoint::AssignLowerByUpper(int upperIndex)
{
	if (upperIndex == 0) {
		return;
	}

	// upperÇäÓÇ…1äKëwâ∫(ç◊Ç©Ç¢)ÇÃÇ‡ÇÃÇ…îΩâfÇ∑ÇÈÅB
	int upperLevel = upperIndex - 1;
	int lowerLevel = upperIndex;
	Logger::Output(LOG_LEVEL::LOG_LEVEL_DEBUG, "assign simple" + to_string(lowerLevel) + " : detail : " + to_string(upperLevel) + "\n");
	auto pDetailRes = m_pDownSampling->GetResolution(upperLevel);
	auto pSimpleRes = m_pDownSampling->GetResolution(lowerLevel);
	for (int j = 0; j < pSimpleRes->GetClusterNum(); j++)
	{
		for (int k = 0; k < pSimpleRes->GetBranchNum(); k++)
		{
			auto index = pSimpleRes->GetToUpper(j, k);
			if (index == AdjancyMatrix::Link::INVALID) {
				continue;
			}

			auto pDetailData = pDetailRes->GetData(index);
			auto pSimpleData = pSimpleRes->GetData(j);
			vec3 quadPos = pSimpleData->QuadPosition() -
				glm::dot(pDetailData->Normal(), pDetailData->QuadPosition() - pDetailData->Position()) * pDetailData->Normal();
			pDetailData->SetQuadPosition(quadPos);
		}
	}

}


void ArrangePoint::Calculate(int localItrNum)
{
	assert(m_pDownSampling != NULL);

	int resolutionIndex = m_pDownSampling->GetResolutionNum() - 1;
	while (resolutionIndex >= 0)
	{
		for (int j = 0; j < 6; j++)
		{
			Logger::Output(LOG_LEVEL::LOG_LEVEL_DEBUG, "Local Alignment" + to_string(resolutionIndex) + "\n");
			LocalArrange(resolutionIndex);

			int globalItr = resolutionIndex;
			while (globalItr >= 0)
			{
				AssignLowerByUpper(globalItr);
				globalItr--;
			}

			//CalcErrorValue();
		}

		resolutionIndex--;
	}

	auto pResolution = m_pDownSampling->GetResolution(0);
	auto pAdjancyMatrix = pResolution->GetAdjancyMatrix();
	for (int i = 0; i < m_pHalfEdgeDS->VertexList().size(); i++)
	{
		auto pVertex = m_pHalfEdgeDS->VertexList()[i];
		pVertex->SetQuadPosition(pResolution->GetData(i)->QuadPosition());
	}

}

void ArrangePoint::InitQuadPosition()
{
	auto pResolution = m_pDownSampling->GetResolution(0);
	auto pAdjancyMatrix = pResolution->GetAdjancyMatrix();
	float sum = 0;
	for (int i = 0; i < m_pHalfEdgeDS->VertexList().size(); i++)
	{
		auto pVertex = m_pHalfEdgeDS->VertexList()[i];

		vec3 pos = glm::normalize(pVertex->Position() + pVertex->Normal());
		m_pHalfEdgeDS->VertexList()[i]->SetQuadPosition(pos);
	}

	for (int i = 0; i < pResolution->GetClusterNum(); i++)
	{
		auto pData = pResolution->GetData(i);
		pData->SetQuadPosition(m_pHalfEdgeDS->VertexList()[i]->QuadPosition());
	}
}

vec3 ArrangePoint::CalcMiddlePoint(const vec3& pos0, const vec3& norm0, const vec3& pos1, const vec3& norm1)
{
	/* ç≈è¨âª |x-p0|^2 + |x-p1|^2 : x = middle point 
	dot(n0, x) == dot(n0, p0)
	dot(n1, x) == dot(n1, p1)
	// ÉâÉOÉâÉìÉWÉÖÇÃñ¢íËèÊêî
	// óùâÇ≈Ç´ÇƒÇ¢Ç»Ç¢ÅB
	*/

	float n0p0 = glm::dot(norm0, pos0);
	float n0p1 = glm::dot(norm0, pos1);
	float n1p0 = glm::dot(norm1, pos0);
	float n1p1 = glm::dot(norm1, pos1);
	float n0n1 = glm::dot(norm0, norm1);

	float denom = 1.0f / (1.0f - n0p1 * n0n1 + 1e-4f);
	float lambda0 = 2.0f*(n0p1 - n0p0 - n0n1 * (n1p0 - n1p1))*denom;
	float lambda1 = 2.0f*(n1p0 - n1p1 - n0n1 * (n0p1 - n0p0))*denom;

	return 0.5f * (pos0 + pos1) - 0.25f *(norm0 * lambda0 + norm1 * lambda1);
}

vec3 ArrangePoint::CalcFloorPosition(
	const vec3& quadPos, const vec3& tangent, const vec3& normal,
	const vec3& middlePos, float scale)
{
	vec3 orient = glm::cross(normal, tangent);
	vec3 dist = middlePos - quadPos;
	float qd = glm::dot(tangent, dist);
	float td = glm::dot(orient, dist);

	vec3 qv = tangent * std::floor(qd / scale) * scale;
	vec3 tv = orient * std::floor(td / scale) * scale;
	vec3 result = quadPos + qv + tv;
	return result;
}

vec3 ArrangePoint::CalcRoundFloorPosition(
	const vec3& quadPos, const vec3& tangent, const vec3& normal,
	const vec3& middlePos, float scale)
{
	vec3 orient = glm::cross(normal, tangent);
	vec3 dist = middlePos - quadPos;
	float qd = glm::dot(tangent, dist);
	float td = glm::dot(orient, dist);

	vec3 qv = tangent * std::round(qd / scale) * scale;
	vec3 tv = orient * std::round(td / scale) * scale;
	vec3 result = quadPos + qv + tv;
	return result;
}

void ArrangePoint::CalcGridPosition(
	const vec3& pos0, const vec3& normal0, const vec3& tangent0, const vec3& quadPos0,
	const vec3& pos1, const vec3& normal1, const vec3& tangent1, const vec3& quadPos1,
	float scale, vec3* ret0, vec3* ret1)
{
	vec3 orient0 = glm::cross(tangent0, normal0);
	vec3 orient1 = glm::cross(tangent1, normal1);
	vec3 middlePos = CalcMiddlePoint(pos0, normal0, pos1, normal1);
	vec3 gridPos0 = CalcFloorPosition(quadPos0, tangent0, normal0, middlePos, scale);
	vec3 gridPos1 = CalcFloorPosition(quadPos1, tangent1, normal1, middlePos, scale);

	vec3 candidate0[4]; 
	candidate0[0] = gridPos0 * scale;
	candidate0[1] = gridPos0 + tangent0 * scale;
	candidate0[2] = gridPos0 + orient0 * scale;
	candidate0[3] = gridPos0 + (tangent0 + orient0)* scale;

	vec3 candidate1[4];
	candidate1[0] = gridPos1 ;
	candidate1[1] = gridPos1 + tangent1 * scale;
	candidate1[2] = gridPos1 + orient1 * scale;
	candidate1[3] = gridPos1 + (tangent1 + orient1)* scale;

	float best_cost = std::numeric_limits<float>::infinity();
	int best_i = -1, best_j = -1;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			float cost = glm::distance(candidate0[i], candidate1[j]);
			if (cost < best_cost)
			{
				best_i = i;
				best_j = j;
				best_cost = cost;
			}

		}
	}

	*ret0 = candidate0[best_i];
	*ret1 = candidate1[best_j];
}

void ArrangePoint::LocalArrange(int level)
{
	auto pResolution = m_pDownSampling->GetResolution(level);
	auto pAdjancyMatrix = pResolution->GetAdjancyMatrix();

	// row ÇÃ index Ç∆ cluster ÇÃ index ÇÕìØÇ∂
	for (int i = 0; i < pAdjancyMatrix->RowNum(); i++)
	{
		auto pLink1 = pAdjancyMatrix->Get(i, 0);
		int vertexIndex1 = pLink1->GetStart();
		auto pVertex1 = pResolution->GetData(vertexIndex1);

		float weight = 0.0f;
		vec3 quadPos = pVertex1->QuadPosition();
		for (int j = 0; j < pAdjancyMatrix->ColumnNum(i); j++)
		{
			auto pLink2 = pAdjancyMatrix->Get(i, j);
			int vertexIndex2 = pLink2->GetEnd();
			auto pVertex2 = pResolution->GetData(vertexIndex2);
			vec3 quadPos1, quadPos2;
			CalcGridPosition(
				pVertex1->Position(), pVertex1->Normal(), quadPos, pVertex1->QuadPosition(),
				pVertex2->Position(), pVertex2->Normal(), pVertex2->Tangent(),pVertex2->QuadPosition(),
				1, &quadPos1, &quadPos2);

			quadPos = quadPos1 * weight + quadPos2 * pLink2->GetWeight();
			quadPos = quadPos - pVertex1->Normal() * glm::dot(pVertex1->Normal(), quadPos - pVertex1->Position())*pVertex1->Normal();
			weight += pLink2->GetWeight();
		}

		if (weight > 0) {
			vec3 quadPos = CalcRoundFloorPosition(quadPos, pVertex1->Tangent(), pVertex1->Normal(), pVertex1->Position(), 1);
			pVertex1->SetQuadPosition(quadPos);
		}
	}
}


}
}