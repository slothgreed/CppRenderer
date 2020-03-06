#ifndef CGAL_MODEL_H
#define CGAL_MODEL_H
namespace KI
{
namespace Asset
{
class DLL_EXPORT CGALModel : public IPolygonModel
{
public:
	CGALModel() {};
	~CGALModel() {};

	virtual void GenSampleModel() = 0;
};
}
}
#endif CGAL_MODEL_H