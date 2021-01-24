#ifndef HALFEDGE_MODEL_H
#define HALFEDGE_MODEL_H
namespace KI
{
namespace Asset
{
class DLL_EXPORT HalfEdgeModel : public IPolygonModel
{
public:
	HalfEdgeModel();
	~HalfEdgeModel();

	virtual MODEL_TYPE Type() override { return MODEL_TYPE::MODEL_TYPE_HALF_EDGE; };
	virtual void Load(const string& filePath);
	virtual void GetFacetList(vector<vec3>& position, vector<vec3>& normal);
	virtual void GetEdgeList(vector<vec3>& edgeList);
	virtual void GetPositionList(vector<vec3>& position);
	virtual bool HasVertexList() { return true; }
	virtual void GetVertexList(vector<Vertex>& vertex);
	virtual void GetEdgeIndexList(vector<int>& index);
	virtual void GetFaceIndexList(vector<int>& index);
	virtual void GetBDB(BDB& bdb);

	shared_ptr<HalfEdgeDS> GetHalfEdgeDS() { return m_HalfEdgeDS; };
	DownSampling* GetDownSampling() { return m_pDownSampling; }
	BVH*		  GetBVH() { return m_pBVH; }
	void CalcDownSampling();
	void CalcBVH();

	void RaycastPick(RaycastPickInfo& result) override;

private:
	shared_ptr<HalfEdgeDS> m_HalfEdgeDS;
	DownSampling* m_pDownSampling;
	BVH*		  m_pBVH;
};
}
}
#endif
