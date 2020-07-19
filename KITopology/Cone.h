#ifndef CONE_H
#define CONE_H

namespace KI
{
namespace Topology
{
// radius = x around;
// height = y value;
//
class DLL_EXPORT Cone : public IPrimitive
{
public:
	Cone();
	~Cone();

	void Build(float radius, float height, int partition);
private:



};
}
}
#endif CONE_H
