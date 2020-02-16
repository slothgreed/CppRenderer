#ifndef IMODEL_H
#define IMODEL_H
namespace KI
{

enum MODEL_TYPE
{
	MODEL_TYPE_HALF_EDGE,
	MODEL_TYPE_CGAL_POLYHEDRON,
	MODEL_TYPE_CGAL_LINEARCELLCOMPLEX,
	MODEL_TYPE_GENERALIZEDMAPS,
	MODEL_TYPE_MOVE_MANIPULATOR
};
class IMaterial;
class IModel : public ISubject
{
public:
	IModel();
	~IModel() {};
	virtual MODEL_TYPE Type() = 0;
	virtual void Load(const std::string& filePath) { assert(0); };
	virtual void Build() { assert(0); };
	virtual void GetFacetList(std::vector<vec3>& position, std::vector<vec3>& normal) { assert(0); };
	virtual void GetEdgeList(std::vector<vec3>& edgeList) { assert(0); };
	virtual void GetPositionList(std::vector<vec3>& position) { assert(0); };
	virtual bool HasVertexList() { return false; }
	virtual void GetVertexList(std::vector<Vertex>& vertex) { assert(0); };
	virtual void GetEdgeIndexList(std::vector<int>& index) { assert(0); };
	virtual void GetFaceIndexList(std::vector<int>& index) { assert(0); };
	virtual void GetBDB(BDB& bdb) = 0;
	virtual void SetMaterial(shared_ptr<IMaterial> material) { m_pMaterial = material; };
	shared_ptr<IMaterial> GetMaterial() { return m_pMaterial; };
protected:
	void SetBDB(BDB bdb);
private:
	BDB m_bdb;
	shared_ptr<IMaterial> m_pMaterial;
};
}
#endif IMODEL_H