#ifndef IRENDER_MODEL_PROPERTY_H
#define IRENDER_MODEL_PROPERTY_H

namespace KI
{
namespace RenderModel
{
enum PROPERTY_TYPE : unsigned int
{
	PROPERTY_TYPE_NORMAL = 0x00,
	PROPERTY_TYPE_HALFEDGE = 0x01,
	PROPERTY_TYPE_RESOLUTION = 0x03,
	PROPERTY_TYPE_BDB = 0x04,
	PROPERTY_TYPE_VERTEX_TANGENT = 0x05,
	PROPERTY_TYPE_BVH = 0x06,
	PROPERTY_TYPE_VERTEX_INDEX = 0x07,
	PROPERTY_TYPE_QUAD_POSITION = 0x08,
	PROPERTY_TYPE_MESH_PARAMETERIZATION = 0x09
};

class DLL_EXPORT IRenderModelPropertyArgs : public IPropertyArgs
{
public:

	IRenderModelPropertyArgs() {};
	~IRenderModelPropertyArgs() {};
	virtual PROPERTY_TYPE PropertyType() = 0;
	virtual unsigned int Type() { return (unsigned int)PropertyType(); }
};
class DLL_EXPORT IRenderModelProperty : public IModelProperty
{
public:

	IRenderModelProperty() {};
	~IRenderModelProperty() {};
	void Build(IModelNode* pModelNode, IPropertyArgs* pPropertyArgs) override;
	virtual void BuildCore(IModelNode* pModelNode, IPropertyArgs* pPropertyArgs) = 0;
	virtual PROPERTY_TYPE PropertyType() = 0;
	virtual unsigned int Type() { return (unsigned int)PropertyType(); }
	virtual void InitializeUI() {};
	virtual void ShowUI() {};

	static shared_ptr<IModelProperty> Create(PROPERTY_TYPE type);
private:

};

}
}

#endif IRENDER_MODEL_PROPERTY_H
