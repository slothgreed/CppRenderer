namespace KI
{
namespace Topology
{

LinkArray::AdjancyMatrix(HalfEdgeDS* pHalfEdgeDS)
	:m_pHalfEdgeDS(pHalfEdgeDS),
	m_size(0),
	m_Matrix(NULL)
{
	New();
}

AdjancyMatrix::~AdjancyMatrix()
{
	Delete();
}

void AdjancyMatrix::New()
{
	assert(m_Matrix == NULL);
	m_size = m_pHalfEdgeDS->VertexList().size();
	m_Matrix = new int*[m_size];
	for (int i = 0; i < m_size; i++)
	{
		int vertexNum = m_pHalfEdgeDS->VertexList()[i]->AroundVertexNum();
		m_Matrix[i] = new int[vertexNum];
		int j = 0;
		for (auto itr = VertexAroundEdgeIterator(m_pHalfEdgeDS->VertexList[i]); itr.HasNext(); itr.Next())
		{
			m_Matrix[i][j] = itr.Current()->Index();
		}
	}
}

void AdjancyMatrix::Delete()
{
	if (m_Matrix != NULL)
	{
		for (int i = 0; i < m_size; i++)
		{
			delete m_Matrix[i];
			m_Matrix[i] = nullptr;
		}

		delete m_Matrix;
		m_Matrix = nullptr;
	}

	m_size = 0;
}

void AdjancyMatrix::Update()
{
	Delete();
	New();
}

}
}