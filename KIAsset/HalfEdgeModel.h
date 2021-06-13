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
	BVH* GetBVH() { return m_pBVH; }
	AlignOrientation* GetAlignOrientation() { return m_pAlignOrientation; }
	DownSampling* GetDownSampling() { return m_pDownSampling; }
	const std::vector<float>& GetShapeDiameterValue() { return m_sdfValue; }
	ShapeDiameterFunction* GetShapeDiameterFunction() { return m_pShapeDiameterFunction; }

	bool CalcBVH();
	void CalcShapeDiameter();
	bool CalcDownSampling();
	bool CalcAlignOrientation();
	bool CalcArrangePosition();

	const std::vector<float>& GetOrientationError();
	const std::vector<float>& GetPositionError();

	void RaycastPick(RaycastPickInfo& result) override;

private:
	shared_ptr<HalfEdgeDS> m_HalfEdgeDS;
	DownSampling* m_pDownSampling;
	AlignOrientation* m_pAlignOrientation;
	ArrangePoint* m_pArrangePoint;
	ShapeDiameterFunction* m_pShapeDiameterFunction;
	std::vector<float> m_sdfValue;
	BVH*		  m_pBVH;
};
}
}
#endif
