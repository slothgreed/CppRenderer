#ifndef ICOSAHEDRON_H
#define ICOSAHEDRON_H

namespace KI
{
namespace Topology
{

class DLL_EXPORT IcosahedronArgs
{
public:
	IcosahedronArgs(float radial, vec3 position) : m_radial(radial) {};
	IcosahedronArgs() :m_radial(1) {};
	float m_radial;
};


class DLL_EXPORT Icosahedron : public IPrimitive
{
public:
	Icosahedron();
	~Icosahedron();

	void Build(const IcosahedronArgs& args);
private:

};



}
}



#endif ICOSAHEDRON_H