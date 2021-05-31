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
};

}
}

#endif SHAPE_DIAMETER_FUNCTION_HPP
