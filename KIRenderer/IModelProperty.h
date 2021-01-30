#ifndef IMODEL_PROPERTY_H
#define IMODEL_PROPERTY_H
namespace KI
{
namespace Renderer
{
class DLL_EXPORT IPropertyArgs
{
public:
	IPropertyArgs() {};
	~IPropertyArgs() {};
	virtual unsigned int Type() = 0;

private:

};

class IModelNode;
class DLL_EXPORT IModelProperty
{
public:
	IModelProperty() {};
	virtual ~IModelProperty() {};

	void SetVisible(bool value) { m_visible = value; }
	bool Visible() { return m_visible; }
	virtual unsigned int Type() = 0;
	virtual void Draw(shared_ptr<UniformStruct> pUniform) = 0;
	virtual void Build(IModelNode* pModelNode, IPropertyArgs* pPropertyArgs) = 0;
	virtual void Update(IModelNode* pModelNode, IPropertyArgs* pPropertyArgs) = 0;
private:
	bool m_visible;
};
}
}
#endif // !IMODEL_PROPERTY_H

