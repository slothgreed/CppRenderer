#ifndef IMODEL_H
#define IMODEL_H
namespace KI
{
class IMaterial;
class IModel : public ISubject
{
public:
	IModel();
	~IModel() {};
	virtual void Load(const std::string& filePath) = 0;
	virtual void GetFacetList(std::vector<vec3>& position, std::vector<vec3>& normal) = 0;
	virtual void GetEdgeList(std::vector<vec3>& edgeList) = 0;
	virtual void GetPositionList(std::vector<vec3>& position) = 0;
	virtual bool HasVertexList() { return false; }
	virtual void GetVertexList(std::vector<Vertex>& vertex) {};
	virtual void GetEdgeIndexList(std::vector<int>& index) {};
	virtual void GetFaceIndexList(std::vector<int>& index) {};
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