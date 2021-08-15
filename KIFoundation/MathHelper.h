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
	static mat4 CreateRotateMatrix(const vec3& source, const vec3& target);
	static float Round(float value, float eps = 0.0001f);
	static float CramesDet(vec3 a, vec3 b, vec3 c);
	static float ToRadian(float angle);
	static float ToAngle(float rad);
	static ivec4 WorldToScreenPos(const mat4x4& proj, const mat4x4& view, const mat4x4& model, const vec3& value);
	static string ToString(const vec2& value);
	static string ToString(const vec3& value);
	static string ToString(const ivec4& value);
	static string ToString(const mat4x4& value);


private:

};
}
}
#endif MATH_HELPER_H