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
	assert(m_Matrix == NULL);
	assert(num == 0);
	assert(m_sizeRow != 0);
	m_sizeRow = num;
	m_Matrix = new Link*[m_sizeRow];
	
}

void AdjancyMatrix::NewColumn(int index, int size)
{
	assert(index < size);
	assert(index != 0);
	m_Matrix[index] = new Link[size];
}

void AdjancyMatrix::Set(int row, int column, const Link& link)
{
	assert(m_sizeRow < row);
	assert(ColumnNum(row) < column);
	m_Matrix[row][column] = link;
}

void AdjancyMatrix::Delete()
{
	if (m_Matrix != NULL)
	{
		for (int i = 0; i < m_sizeRow; i++)
		{
			delete m_Matrix[i];
			m_Matrix[i] = nullptr;
		}

		delete m_Matrix;
		m_Matrix = nullptr;
	}

	m_sizeRow = 0;
}

AdjancyMatrix::Link* AdjancyMatrix::Get(int row, int column)
{
	assert(m_sizeRow < row);
	assert(ColumnNum(row) < column);
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