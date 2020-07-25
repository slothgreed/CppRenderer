#ifndef TORUS_H
#define TORUS_H

namespace KI
{
namespace Topology
{

class DLL_EXPORT TorusArgs
{
public:
	TorusArgs(float _inRad, float _outRad, int _nsides, int _rings) : inRad(_inRad), outRad(_outRad), nsides(_nsides), rings(_rings) {};
	TorusArgs() : inRad(0.5), outRad(1), nsides(32), rings(32) {};
	~TorusArgs() {};

	float inRad;
	float outRad;
	int nsides;
	int rings;
};

class DLL_EXPORT Torus : public IPrimitive
{
public:
	Torus(const TorusArgs& args);
	~Torus();

	void Build(const TorusArgs& args);
private:

};

}
}

#endif TORUS_H
