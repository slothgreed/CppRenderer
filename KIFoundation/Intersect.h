#ifndef INTERSECT_H
#define INTERSECT_H

namespace KI
{
namespace Foundation
{
class DLL_EXPORT Intersect
{
public:
	Intersect();
	~Intersect();

	static bool RayToTriangle(
		const Ray& ray,
		const vec3& p0, const vec3& p1, const vec3& p2,
		vec3& position, float& distance);
private:

};

}
}

#endif INTERSECT_H