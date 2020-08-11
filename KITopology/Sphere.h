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
	SphereArgs(vec3 _position, float _radius, int _slices, int _stacks) : 
		position(_position), radius(_radius), slices(_slices), stacks(_stacks) {};
	~SphereArgs() {};
	float radius;
	int slices;	// z around;
	int stacks;	// z along;
	vec3 position;	// center;
};
class DLL_EXPORT Sphere : public IPrimitive
{
public:
	Sphere(const SphereArgs& args);
	~Sphere();

	void Build(const SphereArgs& args);
private:

};
}
}
#endif SPHERE_H
