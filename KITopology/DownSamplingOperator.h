#ifndef DOWN_SAMPLING_OPERATOR_HPP
#define DOWN_SAMPLING_OPERATOR_HPP

namespace KI
{
namespace Topology
{
class DownSamplingOperator
{
public:
	DownSamplingOperator(DownSampling* pInstance) :m_pInstance(pInstance) {};
	~DownSamplingOperator() {};

	void SetVertexOfCluster();
	void GetData(int level, std::vector<vec3>* position, std::vector<vec3>* normal, std::vector<vec3>* tangent, std::vector<vec3>* quadPos = nullptr);
	void GetCluster(int level, std::vector<int>& index);
	void GetOriginalVertexTangent(int level, std::vector<vec3>* tangents);
private:
	void SetVertexOfClusterRecursive(int level, int upper, std::vector<DownSampling::SampleData>* index);
	void GetClusterRecursive(int level, int upper, int clusterIndex, std::vector<int>& index);
	DownSampling* m_pInstance;
};

}
}
#endif
