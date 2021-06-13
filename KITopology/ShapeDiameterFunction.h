#ifndef SHAPE_DIAMETER_FUNCTION_HPP
#define SHAPE_DIAMETER_FUNCTION_HPP
namespace KI
{
namespace Topology
{
class DLL_EXPORT ShapeDiameterFunction
{
public:
	ShapeDiameterFunction();
	~ShapeDiameterFunction();

	void Calculate(
		float radius,
		int samplingNum,
		HalfEdgeDS* pHalfEdgeDS,
		std::vector<float>& value);

	const std::vector<vec3>& GetTestPos() { return m_testPos; }
	const Ray& GetRay() { return m_ray; }
	const Triangle& GetTri() { return m_triangle; }
private:

	// 計算対象の面の抽出
	void ExtractMesh(
		const std::vector<HalfEdgeFace*>& pFaceList,
		std::vector<HalfEdgeFace*>& extract);
	
	// 点をサンプリング
	void CreateRandomPoint(std::vector<vec4>& position);

	// 円錐の底面向き・位置に変更する
	void TransformPosition(const std::vector<vec4>& position, const vec3& center, const vec3& orient, std::vector<vec3>& circlePos);
	
	float CalculateSDF(
		HalfEdgeFace* pTarget,
		const std::vector<HalfEdgeFace*>& pFaceList,
		const std::vector<vec3>& circlePos);

	float m_radius;
	int m_samplingNum;

	std::vector<vec3> m_testPos;
	Ray m_ray;
	Triangle m_triangle;
};

}
}

#endif SHAPE_DIAMETER_FUNCTION_HPP
