#ifndef SIMULATION_H
#define SIMULATION_H

namespace KI
{
namespace Algorithm
{
class SampleSimulation
{
public:
	SampleSimulation() {};
	~SampleSimulation() {};

	static void RungeKutta(int index, vec2& position, float time, float dt);
private:

};
}
}




#endif SIMULATION_H

