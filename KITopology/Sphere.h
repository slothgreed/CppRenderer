#ifndef SPHERE_H
#define SPHERE_H

namespace KI
{
namespace Topology
{
class DLL_EXPORT SphereArgs
{
public:
	SphereArgs() : position(vec3(0)), radius(1), slices(10), stacks(10){};
	~SphereArgs() {};
	float radius;
	int slices;	// z around;
	int stacks;	// z along;
	vec3 position;	// center;
};
class DLL_EXPORT Sphere : public IPrimitive
{
public:
	Sphere();
	~Sphere();

	void Build(const SphereArgs& args);
private:

};
}
}
#endif SPHERE_H
