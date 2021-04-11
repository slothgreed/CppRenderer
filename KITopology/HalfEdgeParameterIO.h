#ifndef HALFEDGE_PARAMETER_IO_H
#define HALFEDGE_PARAMETER_IO_H

namespace KI
{
namespace Topology
{
class HalfEdgeParameterIO
{
public:
	HalfEdgeParameterIO();
	~HalfEdgeParameterIO();
	void OutputTangent(const std::string& filePath, const vector<vec3>& tangents);
	void LoadTangent(const std::string& filePath, vector<vec3>* tangents);

private:

};
}
}

#endif HALFEDGE_PARAMETER_IO_H