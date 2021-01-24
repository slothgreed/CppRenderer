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
	void GetBVHBoundingBox(int level, std::vector<BDB>& bdb);
private:

	struct DLL_EXPORT Node
	{
		Node() :m_left(NULL), m_right(NULL), m_Index(0) {}
		~Node()
		{
			RELEASE_INSTANCE(m_left);
			RELEASE_INSTANCE(m_right);
		}
		int m_Index;
		BDB m_bdb;
		Node* m_left;
		Node* m_right;
		std::vector<int> m_triangleIndex;
	};

	void MakeTriangleList(const vector<vec3>& positions, const vector<int>& indexs);
	void CalculateRoot();
	void CalculateBDB(Node* pNode);
	void CalculateRecursive(Node* pNode, int index);
	void GetBVHBoundingBoxRecursive(Node* pNode, int level, std::vector<BDB>& bdb);
	BVH::Node m_root;
	std::vector<Triangle> m_triangles;
};

}
}


#endif BVH_H