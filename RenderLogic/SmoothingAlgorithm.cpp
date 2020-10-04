namespace KI
{
namespace Logic
{
SmoothingAlgorithm::SmoothingAlgorithm(HalfEdgeDS* halfEdgeDS)
	: m_halfEdgeDS(halfEdgeDS)
{
}

SmoothingAlgorithm::~SmoothingAlgorithm()
{
}

bool SmoothingAlgorithm::Execute()
{
	HalfEdgeRepository repository(REPOSITORY_DATA_POSITION, m_halfEdgeDS);
	HalfEdgeOperator hoperator;
	hoperator.SmoothingByGravity(m_halfEdgeDS, 1);
	
	repository.Undo();

	return true;
}
}
}
