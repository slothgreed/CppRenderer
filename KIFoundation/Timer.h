#ifndef TIMER_H
#define TIMER_H
#include <chrono>

namespace KI
{
namespace Foundation
{
class DLL_EXPORT Timer
{
public:
	Timer();
	~Timer();

	void Start();
	void WaitForFPS(int fps);
	void PrintFPS();
	void End();
private:
	std::chrono::system_clock::time_point m_beforeTime;
	std::chrono::system_clock::time_point m_startTime;
	std::chrono::system_clock::time_point m_endTime;
	int m_latestFPS;
};

}
}
#endif MOUSE_H