#ifndef HALFEDGE_MODEL_H
#define HALFEDGE_MODEL_H
namespace KI
{
class HalfEdgeModel : public IModel
{
public:
	HalfEdgeModel();
	~HalfEdgeModel();

	virtual void Load(const std::string& filePath);
	virtual void GetFacetList(std::vector<vec3>& position, std::vector<vec3>& normal);
	virtual void GetEdgeList(std::vector<vec3>& edgeList);
	virtual void GetPositionList(std::vector<vec3>& position);
	virtual bool HasVertexList() { return true; }
	virtual void GetVertexList(std::vector<Vertex>& vertex);
	virtual void GetEdgeIndexList(std::vector<int>& index);
	virtual void GetFaceIndexList(std::vector<int>& index);
	virtual void GetBDB(BDB& bdb);

private:
	shared_ptr<HalfEdgeDS> m_HalfEdgeDS;
};

}
#endif
