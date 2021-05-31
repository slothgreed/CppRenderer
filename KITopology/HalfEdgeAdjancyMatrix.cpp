namespace KI
{
namespace Topology
{

HalfEdgeAdjancyMatrix::HalfEdgeAdjancyMatrix(HalfEdgeDS* pHalfEdgeDS)
	: m_pHalfEdgeDS(pHalfEdgeDS)
{
	New();
}

void HalfEdgeAdjancyMatrix::New()
{
	assert(m_pHalfEdgeDS != NULL);
	NewRow((int)m_pHalfEdgeDS->VertexList().size());
	for (int i = 0; i < RowNum(); i++)
	{
		auto vertex = m_pHalfEdgeDS->VertexList()[i];
		int sizeH = vertex->AroundVertexNum();

		NewColumn(i, sizeH);
		int j = 0;
		for (auto itr = VertexAroundEdgeIterator(vertex); itr.HasNext(); itr.Next())
		{
			Set(i, j, Link(vertex->Index(), itr.Current()->End()->Index(), 1.0));
			j++;
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