namespace KI
{
namespace Topology
{

AdjancyMatrix::AdjancyMatrix(HalfEdgeDS* pHalfEdgeDS)
	:m_pHalfEdgeDS(pHalfEdgeDS),
	m_size(0),
	m_Matrix(NULL)
{
	New();
	Calculate();
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
		m_Matrix[i] = new int[m_size];
		for (int j = 0; j < m_size; j++)
		{
			m_Matrix[i][j] = 0;
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
		}

		delete m_Matrix;
	}

	m_size = 0;
}

void AdjancyMatrix::Calculate()
{
	for (int i = 0; i < m_pHalfEdgeDS->EdgeList().size(); i++)
	{
		auto pEdge = m_pHalfEdgeDS->EdgeList()[i];

		m_Matrix[pEdge->Start()->Index()][pEdge->End()->Index()] = 1;
		m_Matrix[pEdge->End()->Index()][pEdge->Start()->Index()] = 1;
	}
}

void AdjancyMatrix::Update()
{
	Delete();
	New();
	Calculate();
}

}
}