#ifndef MATH_HELPER_H
#define MATH_HELPER_H

class MathHelper
{
public:
	MathHelper() {};
	~MathHelper() {};

	static void SphericalToCartesian(float x, float y, glm::vec3& result);
	static void CartesianToSpherical(const glm::vec3& position, float& radian, float& theta, float& phi);
	static std::string ToString(const glm::vec3& value);
private:

};

#endif MATH_HELPER_H