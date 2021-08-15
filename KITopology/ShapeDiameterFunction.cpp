
#include <limits>
namespace KI
{
namespace Topology
{
ShapeDiameterFunction::ShapeDiameterFunction()
{
}

ShapeDiameterFunction::~ShapeDiameterFunction()
{
}

void ShapeDiameterFunction::ExtractMesh(
	const std::vector<HalfEdgeFace*>& pFaceList,
	std::vector < HalfEdgeFace*>& extract)
{
	extract.clear();
	for (int i = 0; i < pFaceList.size(); i++)
	{
		auto pFace = pFaceList[i];
		vec3 position[3];
		pFace->GetVertex(&position[0], &position[1], &position[2]);
		for (int j = 0; j < 3; j++)
		{
			float inner = glm::dot(position[j], -pFace->Normal());
			float len = glm::length(position[j] * sin(inner));
			if (len < m_radius)
			{
				extract.push_back(pFace);
				break;
			}
		}

	}
}
void ShapeDiameterFunction::CreateRandomPoint(std::vector<vec4>& position)
{
	// 回転マトリクスで掛けるので，vec4にしている。
	position.resize(m_samplingNum);
	for (int i = 0; i < m_samplingNum; i++) {
		float len = (Gaccho::rnd(0, 99) + 1) / 100.0;
		float angle = MathHelper::ToRadian(Gaccho::rnd(0, 360));
		position[i] = vec4(std::cos(angle) * len, std::sin(angle) * len, 0.0f, 1.0f);
	}
}
void ShapeDiameterFunction::TransformPosition(const std::vector<vec4>& position, const vec3& center, const vec3& orient, std::vector<vec3>& circlePos)
{
	mat4 matrix = MathHelper::CreateRotateMatrix(vec3(0, 0, 1), orient);
	vec3 movePos = center + orient;
	for (int i = 0; i < position.size(); i++) {
		circlePos[i] = matrix * position[i];
		m_testPos.push_back(circlePos[i] + movePos);
	}
}

float ShapeDiameterFunction::CalculateSDF(
	HalfEdgeFace* pTarget,
	const std::vector<HalfEdgeFace*>& pFaceList,
	const std::vector<vec3>& circlePos)
{
	float minLength = std::numeric_limits<float>::infinity();
	vec3 interPos;

	float sumDist = 0;
	float dist = 0;
	int count = 0;
	vec3 position[3];
	bool skip = false;
	for (int i = 0; i < pFaceList.size(); i++)
	{
		pFaceList[i]->GetVertex(&position[0], &position[1], &position[2]);
		//for (int j = 0; j < 3; j++)
		//{
		//	float inner = glm::dot(position[j], -pFaceList[i]->Normal());
		//	float len = glm::length(position[j] * sin(inner));
		//	if (len < m_radius)
		//	{
		//		skip = true;
		//		break;
		//	}
		//}
		//if (skip) 
		//	continue;

		bool first = true;
		for (int j = 0; j < circlePos.size(); j++)
		{
			vec3 posDir = (circlePos[j] - pTarget->Centroid()) * vec3(100) + pTarget->Centroid();
			Ray ray(pTarget->Centroid(), posDir);
			if (Intersect::RayToTriangle(ray, position[0], position[1], position[2], interPos, dist)) {
				sumDist += dist;
				count++;
				if (first) {
					m_targetTri.push_back(Triangle(position[0], position[1], position[2]));
					first = false;
				}
			}
		}
	}

	if (count == 0) {
		return 0;
	}
	else {
		return sumDist / count;
	}
}
void ShapeDiameterFunction::Calculate(
	float radius,
	int samplingNum,
	HalfEdgeDS* pHalfEdgeDS,
	std::vector<float>& value)
{
	samplingNum = 40;
	PeformanceProfiler profiler;

	profiler.Start();
	m_radius = radius;
	m_samplingNum = samplingNum;
	value.resize(pHalfEdgeDS->FaceList().size());
	std::vector<vec4> randomPos;
	CreateRandomPoint(randomPos);
	std::vector<vec3> circlePos(randomPos.size());
	for (int i = 0; i < pHalfEdgeDS->FaceList().size(); i++)
	{
		auto pFace = pHalfEdgeDS->FaceList()[i];
		Ray ray(pFace->Centroid(), -pFace->Normal());
		TransformPosition(randomPos, ray.Origin(), ray.Direction(), circlePos);
		value[i] =
		CalculateSDF(
			pFace,
			pHalfEdgeDS->FaceList(),
			circlePos);
		m_ray = ray;
		vec3 pos1, pos2, pos3;
		pFace->GetVertex(&pos1, &pos2, &pos3);
		m_triangle = Triangle(pos1, pos2, pos3);
	}

	profiler.End();
	profiler.Output();
}
}
}