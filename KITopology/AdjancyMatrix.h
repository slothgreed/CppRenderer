#ifndef ADJANCY_MATRIX
#define ADJANCY_MATRIX

namespace KI
{
namespace Topology
{
class AdjancyMatrix
{
public:
	AdjancyMatrix(HalfEdgeDS* m_pHalfEdgeDS);
	~AdjancyMatrix();

	void Update();
private:
	void New();
	void Delete();
	void Initialize();
	void Calculate();
	HalfEdgeDS* m_pHalfEdgeDS;
	int** m_Matrix;
	int m_size;
};
}
}

#endif // !HALFEDGE_OPERATOR
