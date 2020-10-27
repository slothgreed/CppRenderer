#ifndef CGAL_POLYHEDRAL_SURFACE_H
#define CGAL_POLYHEDRAL_SURFACE_H
namespace KI
{
namespace Asset
{
class DLL_EXPORT CGALPolyhedron : public ExtLibsModel
{
	
public:
	CGALPolyhedron();
	~CGALPolyhedron();

	virtual MODEL_TYPE Type() override { return MODEL_TYPE::MODEL_TYPE_CGAL_POLYHEDRON; };
	virtual void Load(const std::string& filePath);
	virtual void GetFacetList(std::vector<vec3>& position, std::vector<vec3>& normal);
	virtual void GetEdgeList(std::vector<vec3>& edgeList);
	virtual void GetPositionList(std::vector<vec3>& position);
	virtual void GetBDB(BDB& bdb);
	virtual void GenSampleModel();

private:

	class CGALPolyhedronImpl* m_pPrivate;
	
};
}
}
#endif CGAL_POLYHEDRAL_SURFACE_H