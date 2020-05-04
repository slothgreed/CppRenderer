#ifndef MATH_HELPER_H
#define MATH_HELPER_H
namespace KI
{
namespace Foundation
{
class DLL_EXPORT MathHelper
{
public:
	MathHelper() {};
	~MathHelper() {};

	static void SphericalToCartesian(float radius, float x, float y, vec3& result);
	static void CartesianToSpherical(const vec3& position, float& radian, float& theta, float& phi);
	static float CalcTriangleArea(const vec3& v1, const vec3& v2, const vec3& v3); // counter cloclk wise
	static void CalcNormal(const vec3& v1, const vec3& v2, const vec3& v3, vec3& normal); // counter cloclk wise
	static float CalcRadian(const vec3& v1, const vec3& v2);
	static float CramesDet(vec3 a, vec3 b, vec3 c);
	static std::string ToString(const vec3& value);
	static bool IntersectionRayToTriangle(
		const vec3& origin, const vec3& direction,
		const vec3& p0, const vec3& p1, const vec3& p2,
		vec3& position, float& distance);

private:

};
}
}
#endif MATH_HELPER_H