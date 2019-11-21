#ifndef IMODEL_PROPERTY_H
#define IMODEL_PROPERTY_H
namespace KI
{
enum PROPERTY_TYPE
{
	PROPERTY_TYPE_BDB
};

class IModelProperty
{
public:
	IModelProperty() {};
	~IModelProperty() {};

	virtual PROPERTY_TYPE Type() = 0;
	void SetVisible(bool value) { m_visible = value; }
	bool Visible() { return m_visible; }
	virtual void Draw() = 0;
private:
	bool m_visible;
};
}
#endif // !IMODEL_PROPERTY_H



