#ifndef IMODEL_PROPERTY_H
#define IMODEL_PROPERTY_H
namespace KI
{
namespace Renderer
{
enum PROPERTY_TYPE
{
	PROPERTY_TYPE_VECTOR,
	PROPERTY_TYPE_HALFEDGE,
	PROPERTY_TYPE_BDB
};

class DLL_EXPORT IModelProperty
{
public:
	IModelProperty() {};
	virtual ~IModelProperty() {};

	virtual PROPERTY_TYPE Type() = 0;
	void SetVisible(bool value) { m_visible = value; }
	bool Visible() { return m_visible; }
	virtual void Draw() = 0;
	virtual void Update(IModel* model) = 0;
	virtual void Build(IModel* pModel) = 0;
private:
	bool m_visible;
};
}
}
#endif // !IMODEL_PROPERTY_H

