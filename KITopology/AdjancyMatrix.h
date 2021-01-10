#ifndef ADJANCY_MATRIX_HPP
#define ADJANCY_MATRIX_HPP

namespace KI
{
namespace Topology
{
// Has Link Array;
// m_Matrix[i][j] = (vertex->Index(),vertex->AroundVertex(j)->Index());
class DLL_EXPORT AdjancyMatrix
{
public:
	class DLL_EXPORT Link
	{
	public:
		Link() :m_start(-1), m_end(-1), m_weight(0.0f) {};
		Link(int start, int end, float weight)
			:m_start(start), m_end(end), m_weight(weight) {};
		~Link() {};
		void Set(int start, int end, float weight);
		void SetStart(int start);
		void SetEnd(int end);
		void SetWeight(float weight);
		int GetStart() { return m_start; };
		int GetEnd() { return m_end; };
		float GetWeight() { return m_weight; };

		inline bool operator<(const Link& link) const { return m_end < link.m_end; }
	private:
		int m_start;
		int m_end;
		float m_weight;
	};

	AdjancyMatrix();
	virtual ~AdjancyMatrix();

	void Set(int row, int column, const Link& link);
	int RowNum() { return m_sizeRow; }
	int ColumnNum(int i);
	AdjancyMatrix::Link* Get(int row, int column);
	virtual void NewRow(int num);
	virtual void NewColumn(int index, int num);
protected:
	virtual void Delete();
	std::vector<std::vector<AdjancyMatrix::Link>> m_Matrix;
private:
	HalfEdgeDS* m_pHalfEdgeDS;
	int m_sizeRow;
};
}
}

#endif // !ADJANCY_MATRIX_HPP
