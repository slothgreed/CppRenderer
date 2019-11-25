#ifndef CGAL_LINEAR_CELL_COMPLEX_H
#define CGAL_LINEAR_CELL_COMPLEX_H
namespace KI
{
class CGALLinearCellComplex : public CGALModel
{
public:
	CGALLinearCellComplex();
	~CGALLinearCellComplex();

	virtual void Load(const std::string& filePath);
	virtual void GenSampleModel();
	virtual void GetFacetList(std::vector<vec3>& position, std::vector<vec3>& normal);
	virtual void GetEdgeList(std::vector<vec3>& edgeList);
	virtual void GetPositionList(std::vector<vec3>& position);
	virtual void GetBDB(BDB& bdb);
private:

};
}
#endif CGAL_LINEAR_CELL_COMPLEX_H