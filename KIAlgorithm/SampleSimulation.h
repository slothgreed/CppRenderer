#ifndef SIMULATION_H
#define SIMULATION_H

namespace KI
{
namespace Algorithm
{
class DLL_EXPORT SampleSimulation
{
public:
	SampleSimulation() {};
	~SampleSimulation() {};

	static void RungeKutta(const vec3& position, float time, float dt, vec3& result);
private:

};
}
}




#endif SIMULATION_H

