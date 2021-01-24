#ifndef IMODEL_PROPERTY_H
#define IMODEL_PROPERTY_H
namespace KI
{
namespace Renderer
{
enum PROPERTY_TYPE : unsigned int
{
	PROPERTY_TYPE_VECTOR = 0x00,
	PROPERTY_TYPE_HALFEDGE = 0x01,
	PROPERTY_TYPE_HALFEDGE_CLUSTER = 0x03,
	PROPERTY_TYPE_BDB = 0x04,
	PROPERTY_TYPE_VERTEX_TANGENT = 0x05,
	PROPERTY_TYPE_BVH = 0x06

};

class DLL_EXPORT IPropertyArgs
{
public:
	IPropertyArgs() {};
	~IPropertyArgs() {};
	virtual PROPERTY_TYPE Type() = 0;

private:

};

class IModelNode;
class DLL_EXPORT IModelProperty
{
public:
	IModelProperty() {};
	virtual ~IModelProperty() {};

	virtual PROPERTY_TYPE Type() = 0;
	void SetVisible(bool value) { m_visible = value; }
	bool Visible() { return m_visible; }
	virtual void Draw(shared_ptr<UniformStruct> pUniform) = 0;
	virtual void Build(IModelNode* pModelNode, IPropertyArgs* pPropertyArgs) = 0;
	virtual void Update(IModelNode* pModelNode, IPropertyArgs* pPropertyArgs) = 0;
private:
	bool m_visible;
};
}
}
#endif // !IMODEL_PROPERTY_H

