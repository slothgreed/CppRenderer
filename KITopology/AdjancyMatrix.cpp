namespace KI
{
namespace Topology
{

AdjancyMatrix::AdjancyMatrix()
	: m_sizeRow(0),
	m_Matrix(NULL)
{
}

AdjancyMatrix::~AdjancyMatrix()
{
	Delete();
}

void AdjancyMatrix::NewRow(int num)
{
	assert(num != 0);
	assert(m_sizeRow == 0);
	m_sizeRow = num;

	m_Matrix.resize(num);
}

void AdjancyMatrix::NewColumn(int index, int size)
{
	assert(index < m_sizeRow);
	m_Matrix[index].resize(size);
}

void AdjancyMatrix::Set(int row, int column, const Link& link)
{
	assert(m_sizeRow > row);
	assert(ColumnNum(row) > column);
	m_Matrix[row][column] = link;
}

int AdjancyMatrix::ColumnNum(int i)
{
	return (int)m_Matrix[i].size();
}

void AdjancyMatrix::Delete()
{
	m_Matrix.clear();
	m_sizeRow = 0;
}

AdjancyMatrix::Link* AdjancyMatrix::Get(int row, int column)
{
	assert(m_sizeRow >= row);
	assert(ColumnNum(row) >= column);
	return &m_Matrix[row][column];
}



void AdjancyMatrix::Link::Set(int start, int end, float weight) 
{
	m_start = start;
	m_end = end;
	m_weight = weight;
}

void AdjancyMatrix::Link::SetStart(int start)
{
	m_start = start;
}

void AdjancyMatrix::Link::SetEnd(int end)
{
	m_end = end;
}

void AdjancyMatrix::Link::SetWeight(float weight)
{
	m_weight = weight;
}
}
}