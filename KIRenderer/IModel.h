#ifndef IMODEL_H
#define IMODEL_H

namespace KI
{
namespace Renderer
{
enum MODEL_TYPE
{
	MODEL_TYPE_HALF_EDGE,
	MODEL_TYPE_CGAL_POLYHEDRON,
	MODEL_TYPE_CGAL_LINEARCELLCOMPLEX,
	MODEL_TYPE_GENERALIZEDMAPS,
	MODEL_TYPE_MOVE_MANIPULATOR
};

class DLL_EXPORT IModel : public ISubject
{
public:
	IModel() { };
	virtual ~IModel() {};
	virtual MODEL_TYPE Type() = 0;
	virtual void GetBDB(BDB& bdb) = 0;
protected:
	void SetBDB(BDB value) { m_bdb = value; };
private:
	BDB m_bdb;
private:

};
}
}
#endif IMODEL_H