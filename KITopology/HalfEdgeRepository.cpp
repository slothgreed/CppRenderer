namespace KI
{
namespace Topology
{
HalfEdgeRepository::HalfEdgeRepository(REPOSITORY_DATA repoData, HalfEdgeDS* halfEdgeDS) :
	m_RepositoryData(repoData),
	m_halfEdgeDS(halfEdgeDS)
{
}
HalfEdgeRepository::~HalfEdgeRepository()
{

}

void HalfEdgeRepository::Repository()
{
	if (m_RepositoryData == REPOSITORY_DATA_POSITION)
	{
		RepositoryPosition(m_halfEdgeDS);
	}

}
void HalfEdgeRepository::RepositoryPosition(HalfEdgeDS* halfEdgeDS)
{
	m_position.resize(halfEdgeDS->VertexList().size());
	for (int i = 0; i < halfEdgeDS->VertexList().size(); i++)
	{
		m_position[i] = halfEdgeDS->VertexList()[i]->Position();
	}
}

void HalfEdgeRepository::Undo()
{
	for (int i = 0; i < m_position.size(); i++)
	{
		m_halfEdgeDS->VertexList()[i]->SetPosition(m_position[i]);
	}

	m_halfEdgeDS->CalcElement();
}


}
}