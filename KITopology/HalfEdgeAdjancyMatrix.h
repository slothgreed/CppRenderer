#ifndef HALF_EDGE_ADJANCY_MATRIX_HPP
#define HALF_EDGE_ADJANCY_MATRIX_HPP

namespace KI
{
namespace Topology
{
// Has Link Array;
// m_Matrix[i][j] = (vertex->Index(),vertex->AroundVertex(j)->Index());
	class HalfEdgeAdjancyMatrix : AdjancyMatrix
{
public:
	
	HalfEdgeAdjancyMatrix(HalfEdgeDS* m_pHalfEdgeDS);
	~HalfEdgeAdjancyMatrix() {};

	int Size() { return m_sizeW * m_sizeH; }
	int PositionNum() { return m_sizeW; }
	int AroundPositionNum(int i) { return m_Matrix[i + 1] - m_Matrix[i]; }
	virtual void NewRow(int num) { assert(0); };
	virtual void NewColumn(int index, int num) { assert(0); };
	void Update();
	
private:
	void New();
	HalfEdgeDS* m_pHalfEdgeDS;
	Link** m_Matrix;
	int m_sizeW;
	int m_sizeH;
};
}
}
#endif // !HALF_EDGE_ADJANCY_MATRIX_HPP
