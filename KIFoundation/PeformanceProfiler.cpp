#include <time.h>
namespace KI
{
namespace Foundation
{
PeformanceProfiler::PeformanceProfiler()
{
}

PeformanceProfiler::~PeformanceProfiler()
{
}

void PeformanceProfiler::Start()
{
	m_start = clock();
}

void PeformanceProfiler::End()
{
	clock_t end = clock();
	m_duration = (end - m_start) / CLOCKS_PER_SEC;
}

void PeformanceProfiler::Output()
{
	Logger::Output(LOG_LEVEL::LOG_LEVEL_WARNING, to_string(m_duration) + "\n");
}

}
}