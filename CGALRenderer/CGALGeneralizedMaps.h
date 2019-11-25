#ifndef CGAL_GENERALIZED_MAPS_H
#define CGAL_GENERALIZED_MAPS_H
namespace KI
{
class CGALGeneralizedMaps : public CGALModel
{
public:
	CGALGeneralizedMaps();
	~CGALGeneralizedMaps();

	virtual void Load(const std::string& filePath);
	virtual void GenSampleModel();
	virtual void GetFacetList(std::vector<vec3>& position, std::vector<vec3>& normal);
	virtual void GetEdgeList(std::vector<vec3>& edgeList);
	virtual void GetPositionList(std::vector<vec3>& position);
	virtual void GetBDB(BDB& bdb);
private:

};
}
#endif CGAL_GENERALIZED_MAPS_H