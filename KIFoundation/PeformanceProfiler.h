#ifndef PEFORMANCE_PROFILER_H
#define PEFORMANCE_PROFILER_H

namespace KI
{
namespace Foundation
{

class DLL_EXPORT PeformanceProfiler
{
public:
	PeformanceProfiler();
	~PeformanceProfiler();

	void Start();
	void End();
	void Output();
private:
	long m_duration;
	long m_start;
};

}
}


#endif PEFORMANCE_PROFILER_H