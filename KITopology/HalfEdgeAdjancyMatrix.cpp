namespace KI
{
namespace Topology
{

HalfEdgeAdjancyMatrix::HalfEdgeAdjancyMatrix(HalfEdgeDS* pHalfEdgeDS)
	:m_sizeW(0),
	m_sizeH(0),
	m_Matrix(NULL)
{
	New();
}

HalfEdgeAdjancyMatrix::~HalfEdgeAdjancyMatrix()
{
}

void HalfEdgeAdjancyMatrix::New()
{
	assert(m_Matrix == NULL);
	m_sizeW = m_pHalfEdgeDS->VertexList().size();
	m_Matrix = new Link*[m_sizeW];
	for (int i = 0; i < m_sizeW; i++)
	{
		auto vertex = m_pHalfEdgeDS->VertexList()[i];
		m_sizeH = vertex->AroundVertexNum();
		m_Matrix[i] = new Link[m_sizeH];
		int j = 0;
		for (auto itr = VertexAroundEdgeIterator(vertex.get()); itr.HasNext(); itr.Next())
		{
			m_Matrix[i][j] = Link(vertex->Index(), itr.Current()->Index(), 0);
		}
	}
}

void HalfEdgeAdjancyMatrix::Update()
{
	Delete();
	New();
}

}
}