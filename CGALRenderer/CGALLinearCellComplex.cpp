#include "CGAL/Linear_cell_complex_for_combinatorial_map.h"

CGALLinearCellComplex::CGALLinearCellComplex()
{
}

CGALLinearCellComplex::~CGALLinearCellComplex()
{
}

void CGALLinearCellComplex::Load(const std::string& filePath)
{

}

void CGALLinearCellComplex::GenSampleModel()
{
	typedef CGAL::Linear_cell_complex_for_combinatorial_map<3> LCC;
	typedef LCC::Dart_handle DartHandle;
	typedef LCC::Point Point;

	LCC lcc;
	DartHandle dh1 =
		lcc.make_hexahedron(Point(0, 0, 0), Point(5, 0, 0),
			Point(5, 5, 0), Point(0, 5, 0),
			Point(0, 5, 4), Point(0, 0, 4),
			Point(5, 0, 4), Point(5, 5, 4));
	DartHandle dh2 =
		lcc.make_hexahedron(Point(5, 0, 0), Point(10, 0, 0),
			Point(10, 5, 0), Point(5, 5, 0),
			Point(5, 5, 4), Point(5, 0, 4),
			Point(10, 0, 4), Point(10, 5, 4));

	lcc.sew<3>(lcc.beta(dh1, 1, 1, 2), lcc.beta(dh2, 2));
}

void CGALLinearCellComplex::GetFacetList(std::vector<vec3>& position, std::vector<vec3>& normal)
{

}

void CGALLinearCellComplex::GetEdgeList(std::vector<vec3>& edgeList)
{

}

void CGALLinearCellComplex::GetVertexList(std::vector<vec3>& position)
{

}

void CGALLinearCellComplex::GetBDB(BDB& bdb)
{

}