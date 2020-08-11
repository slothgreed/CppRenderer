#ifndef AXIS_H
#define AXIS_H
namespace KI
{
namespace Asset
{

class DLL_EXPORT AxisArgs
{
public:
	AxisArgs() :min(vec3(0)), max(vec3(1)) {}
	AxisArgs(vec3 min, vec3 max) :min(vec3(0)), max(vec3(1)) {}
	vec3 min;
	vec3 max;
};
class  DLL_EXPORT Axis : public IPrimitive
{

public:
	Axis(const AxisArgs& args);
	~Axis();
	void Build(const AxisArgs& args);

private:

};


}
}
#endif AXIS_H
