#ifndef QUAD_H
#define QUAD_H

namespace KI
{
namespace Topology
{

class DLL_EXPORT QuadArgs
{
public:
	QuadArgs() : m_min(vec2(0)), m_max(vec2(1)) {};
	QuadArgs(const vec2& min, const vec2& max) : m_min(min), m_max(max) {};
	vec2 m_max;
	vec2 m_min;
};

class DLL_EXPORT Quad : public IPrimitive
{
	
public:
	Quad();
	~Quad();

	void Build(const QuadArgs& args);
private:

};
}
}

#endif