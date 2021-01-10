#ifndef HALF_EDGE_ADJANCY_MATRIX_HPP
#define HALF_EDGE_ADJANCY_MATRIX_HPP

namespace KI
{
namespace Topology
{
// Has Link Array;
// m_Matrix[i][j] = (vertex->Index(),vertex->AroundVertex(j)->Index());
class DLL_EXPORT HalfEdgeAdjancyMatrix : public AdjancyMatrix
{
public:
	
	HalfEdgeAdjancyMatrix(HalfEdgeDS* m_pHalfEdgeDS);
	~HalfEdgeAdjancyMatrix() {};

	int PositionNum() { return RowNum(); }
	int AroundPositionNum(int i) { return ColumnNum(i); }
	void Update();
	
private:
	void New();
	HalfEdgeDS* m_pHalfEdgeDS;
};
}
}
#endif // !HALF_EDGE_ADJANCY_MATRIX_HPP
