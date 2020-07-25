#ifndef CONE_H
#define CONE_H

namespace KI
{
namespace Topology
{

class DLL_EXPORT ConeArgs
{
public:
	ConeArgs(float _radius, float _height,int _partition) : radius(_radius), height(_height), partition(_partition) {};
	ConeArgs() : radius(1), height(1), partition(32) {};
	~ConeArgs() {};

	float radius;
	float height;
	int partition;
};
// radius = x around;
// height = y value;
//
class DLL_EXPORT Cone : public IPrimitive
{
public:
	Cone();
	~Cone();

	void Build(const ConeArgs& args);
private:



};
}
}
#endif CONE_H
