#ifndef CGAL_MODEL_H
#define CGAL_MODEL_H
namespace KI
{
class CGALModel : public IModel
{
public:
	CGALModel() {};
	~CGALModel() {};

	virtual void GenSampleModel() = 0;
};
}
#endif CGAL_MODEL_H