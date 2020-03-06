namespace KI
{
namespace Asset
{

bool IPolygonModel::IsPolygonModel(MODEL_TYPE type)
{
	if (type == MODEL_TYPE_HALF_EDGE ||
		type == MODEL_TYPE_CGAL_POLYHEDRON ||
		type == MODEL_TYPE_CGAL_LINEARCELLCOMPLEX)
	{
		return true;
	}
	else
	{
		return false;
	}
}
}
}