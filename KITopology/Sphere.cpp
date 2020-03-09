#include "Sphere.h"
namespace KI
{
namespace Topology
{
Sphere::Sphere()
{
}

Sphere::~Sphere()
{
}

void Sphere::Build(const SphereArgs& args)
{

	float theta = pi<float>() / args.slices;
	float phi = pi<float>() / args.stacks;
	vec3 result;


	MathHelper::SphericalToCartesian(args.radius, theta, phi, result);
}
}
}