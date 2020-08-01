#ifndef CYLINDER_H
#define CYLINDER_H

namespace KI
{
namespace Topology
{

class DLL_EXPORT CylinderArgs
{
public:
	CylinderArgs(float _baseRad, float _topRad,float _height,int _slices) :
		baseRad(_baseRad),
		topRad(_topRad),
		height(_height),
		slices(_slices)
	{};
	CylinderArgs() :
		baseRad(1),
		topRad(1),
		height(1),
		slices(5)
	{};
	~CylinderArgs() {};

	float baseRad;
	float topRad;
	float height;
	int slices;
};
// radius = x around;
// height = y value;
//
class DLL_EXPORT Cylinder : public IPrimitive
{
public:
	Cylinder(const CylinderArgs& args);
	~Cylinder();

	void Build(const CylinderArgs& args);
private:



};
}
}
#endif CYLINDER_H