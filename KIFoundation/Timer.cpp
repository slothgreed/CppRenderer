#include<thread>
using namespace chrono;
namespace KI
{
namespace Foundation
{
Timer::Timer()
{
}

Timer::~Timer()
{
}

void Timer::Start()
{
	m_startTime = system_clock::now();
	m_beforeTime =  system_clock::now();
}


void Timer::WaitForFPS(int fps)
{
	auto current = system_clock::now();
	auto duration = duration_cast<milliseconds>(current - m_beforeTime).count();
	double fpsDuration = 1000.0 / fps;
	if (duration == 0)
	{
		return;
	}

	m_latestFPS = (int)(1000 / duration);

	if (duration < fpsDuration)
	{
		std::this_thread::sleep_for(chrono::milliseconds((int)(fpsDuration - duration)));
		//Logger::Output(LOG_LEVEL::DEBUG, "FPS " + to_string(m_latestFPS) + " : duration" + to_string(duration) + ": sleep" + to_string(fpsDuration - duration) + "\n");
	}
	else
	{
		//Logger::Output(LOG_LEVEL::DEBUG, "FPS " + to_string(m_latestFPS) + " : duration" + to_string(duration) + "\n");
	}

	m_beforeTime = current;
}
void Timer::PrintFPS()
{

}

void Timer::End()
{
	m_endTime = system_clock::now();
}


}
}
