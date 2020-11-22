#ifndef ADJANCY_MATRIX
#define ADJANCY_MATRIX

namespace KI
{
namespace Topology
{
// Has Link Array;
// m_Matrix[i][j] = (vertex->Index(),vertex->AroundVertex(j)->Index());
class AdjancyMatrix
{
public:
	AdjancyMatrix(HalfEdgeDS* m_pHalfEdgeDS);
	~AdjancyMatrix();

	void Update();
private:
	void New();
	void Delete();
	HalfEdgeDS* m_pHalfEdgeDS;
	int** m_Matrix;
	int m_size;
};
}
}

#endif // !HALFEDGE_OPERATOR
