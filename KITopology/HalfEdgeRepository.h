#ifndef HALF_EDGE_REPOSITORY_H
#define HALF_EDGE_REPOSITORY_H

namespace KI
{
namespace Topology
{
enum REPOSITORY_DATA
{
	REPOSITORY_DATA_POSITION
};

class DLL_EXPORT HalfEdgeRepository
{
public:
	HalfEdgeRepository(REPOSITORY_DATA repoData, HalfEdgeDS* halfEdge);
	~HalfEdgeRepository();

	void Repository();
	void Undo();
private:
	void RepositoryPosition(HalfEdgeDS* halfEdge);

	REPOSITORY_DATA m_RepositoryData;
	HalfEdgeDS* m_halfEdgeDS;

	vector<vec3> m_position;
};

}
}


#endif HALF_EDGE_REPOSITORY_H