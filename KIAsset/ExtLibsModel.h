#ifndef CGAL_MODEL_H
#define CGAL_MODEL_H
namespace KI
{
namespace Asset
{
class DLL_EXPORT ExtLibsModel : public IPolygonModel
{
public:
	ExtLibsModel() {};
	~ExtLibsModel() {};

	virtual void GenSampleModel() = 0;
};
}
}
#endif CGAL_MODEL_H