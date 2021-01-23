#ifndef BVH_H
#define BVH_H

namespace KI
{
namespace Topology
{

class DLL_EXPORT BVH
{
public:
	BVH();
	~BVH();

	void Calculate(const vector<vec3>& positions, const vector<int>& index);
private:

	struct Node
	{
		Node() :m_left(NULL), m_right(NULL) {}
		~Node()
		{
			RELEASE_INSTANCE(m_left);
			RELEASE_INSTANCE(m_right);
		}
		const int INVALID = -1;
		BDB m_bdb;
		Node* m_left;
		Node* m_right;
		std::vector<int> m_triangleIndex;
	};

	void MakeTriangleList(const vector<vec3>& positions, const vector<int>& indexs);
	void CalculateRoot();
	void CalculateBDB(Node* pNode);
	void CalculateRecursive(Node* pNode, int index);
	BVH::Node m_root;
	std::vector<Triangle> m_triangles;
};

}
}


#endif BVH_H