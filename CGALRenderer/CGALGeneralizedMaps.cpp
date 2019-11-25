#include "CGAL/Generalized_map.h"
namespace KI
{

CGALGeneralizedMaps::CGALGeneralizedMaps()
{
}

CGALGeneralizedMaps::~CGALGeneralizedMaps()
{
}

void CGALGeneralizedMaps::Load(const std::string& filePath)
{

}

void CGALGeneralizedMaps::GenSampleModel()
{
	typedef CGAL::Generalized_map<3> GMAP;
	typedef GMAP::Dart_handle DartHandle;
	typedef GMAP::size_type sizeType;
	typedef GMAP::Dart_of_cell_range<3>::iterator DartCellIterator;
	typedef GMAP::Dart_range::iterator DartRangeIterator;
	GMAP gmap;
	sizeType amark;

	amark = gmap.get_new_mark();

	DartHandle dh1 = gmap.make_combinatorial_tetrahedron();
	DartHandle dh2 = gmap.make_combinatorial_tetrahedron();


	CGAL_assertion(gmap.is_valid());
	CGAL_assertion(gmap.is_volume_combinatorial_tetrahedron(dh1));
	CGAL_assertion(gmap.is_volume_combinatorial_tetrahedron(dh2));

	gmap.sew<3>(dh1, dh2);

	for (DartCellIterator it(gmap.darts_of_cell<3>(dh1).begin()),itend(gmap.darts_of_cell<3>(dh1).end());
		it != itend; ++it)
	{
		gmap.mark(it, amark);
	}

	gmap.remove_cell<2>(dh1);

	unsigned int res = 0;

	for (DartRangeIterator it(gmap.darts().begin()), itend(gmap.darts().end()); it != itend; ++it)
	{
		if (gmap.is_marked(it, amark)) 
		{
			++res;
		}
	}

	gmap.free_mark(amark);
}

void CGALGeneralizedMaps::GetFacetList(std::vector<vec3>& position, std::vector<vec3>& normal)
{

}

void CGALGeneralizedMaps::GetEdgeList(std::vector<vec3>& edgeList)
{

}

void CGALGeneralizedMaps::GetPositionList(std::vector<vec3>& position)
{

}

void CGALGeneralizedMaps::GetBDB(BDB& bdb)
{

}
}