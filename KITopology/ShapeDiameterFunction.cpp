#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
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
	const std::vector<shared_ptr<HalfEdgeFace>>& pFaceList,
	std::vector < shared_ptr<HalfEdgeFace>>& extract)
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
			if ((position[j] * sin(inner)).length() < m_radius)
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
		float len = Gaccho::rnd(0, m_radius);
		float angle = MathHelper::ToRadian(Gaccho::rnd(0, 360));
		position[i] = vec4(std::cos(angle) * len, std::sin(angle) * len, 0.0f, 0.0f);
	}
}
void ShapeDiameterFunction::TransformPosition(const std::vector<vec4>& position, const vec3& center, const vec3& orient, std::vector<vec3>& circlePos)
{
	// angle は0
	quat axis = angleAxis(0.0f, vec3(orient.x, orient.y, orient.z));
	mat4 matrix = glm::toMat4(axis);

	for (int i = 0; i < position.size(); i++) {
		circlePos[i] = matrix * position[i];
	}
}

float ShapeDiameterFunction::CalculateSDF(
	HalfEdgeFace* pTarget,
	const std::vector<shared_ptr<HalfEdgeFace>>& pFaceList,
	const std::vector<vec3>& circlePos)
{
	float minLength = std::numeric_limits<float>::infinity();
	vec3 pos0, pos1, pos2;
	vec3 interPos;
	float dist;
	std::vector<shared_ptr<HalfEdgeFace>> extractFace;
	ExtractMesh(pFaceList, extractFace);
	if (extractFace.size() == 0)
	{
		return 0;
	}
	for (int i = 0; i < circlePos.size(); i++) {
		Ray ray(pTarget->Gravity(), circlePos[i]);
		for (int j = 0; j < extractFace.size(); j++)
		{
			extractFace[j]->GetVertex(&pos0, &pos1, &pos2);
			if (Intersect::RayToTriangle(ray, pos0, pos1, pos2, interPos, dist)) {
				if (dist < minLength)
				{
					minLength = dist;
				}
			}
		}
	}

	return minLength;
}
void ShapeDiameterFunction::Calculate(
	float radius,
	int samplingNum,
	HalfEdgeDS* pHalfEdgeDS,
	std::vector<float>& value)
{
	m_radius = radius;
	m_samplingNum = samplingNum;
	value.resize(pHalfEdgeDS->FaceList().size());
	std::vector<vec4> randomPos;
	CreateRandomPoint(randomPos);
	std::vector<vec3> circlePos(randomPos.size());
	for (int i = 0; i < pHalfEdgeDS->FaceList().size(); i++)
	{
		auto pFace = pHalfEdgeDS->FaceList()[i];
		Ray ray(pFace->Gravity(), -pFace->Normal());
		TransformPosition(randomPos, ray.Origin() + ray.Direction(), ray.Direction(), circlePos);
		value[i] = CalculateSDF(
			pFace.get(),
			pHalfEdgeDS->FaceList(),
			circlePos);
		Logger::Output(LOG_LEVEL::LOG_LEVEL_WARNING, to_string(i) + ":" + to_string(value[i]) + "\n");
	}
}
}
}