#ifndef HALFEDGE_MODEL_H
#define HALFEDGE_MODEL_H
namespace KI
{
class HalfEdgeModel : public IPolygonModel
{
public:
	HalfEdgeModel();
	~HalfEdgeModel();

	virtual MODEL_TYPE Type() override { return MODEL_TYPE::MODEL_TYPE_HALF_EDGE; };
	virtual void Load(const std::string& filePath);
	virtual void GetFacetList(std::vector<vec3>& position, std::vector<vec3>& normal);
	virtual void GetEdgeList(std::vector<vec3>& edgeList);
	virtual void GetPositionList(std::vector<vec3>& position);
	virtual bool HasVertexList() { return true; }
	virtual void GetVertexList(std::vector<Vertex>& vertex);
	virtual void GetEdgeIndexList(std::vector<int>& index);
	virtual void GetFaceIndexList(std::vector<int>& index);
	virtual void GetBDB(BDB& bdb);

	shared_ptr<HalfEdgeDS> GetHalfEdgeDS() { return m_HalfEdgeDS; };
private:
	shared_ptr<HalfEdgeDS> m_HalfEdgeDS;
};

}
#endif
