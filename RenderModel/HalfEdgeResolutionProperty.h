#ifndef HALF_EDGE_RESOLUTION_PROPERTY_H
#define HALF_EDGE_RESOLUTION_PROPERTY_H

namespace KI
{
namespace RenderModel
{

class DLL_EXPORT HalfEdgeResolutionPropertyArgs : public IPropertyArgs
{
	friend class HalfEdgeResolutionProperty;
public:
	HalfEdgeResolutionPropertyArgs(int level) :m_level(level) {};
	~HalfEdgeResolutionPropertyArgs() {};
	virtual PROPERTY_TYPE Type() override { return PROPERTY_TYPE_HALFEDGE_CLUSTER; }

	int Level() { return m_level; }
private:
	int m_level;
};

class DLL_EXPORT HalfEdgeResolutionProperty : public IModelProperty
{
public:
	HalfEdgeResolutionProperty();
	~HalfEdgeResolutionProperty() {};

	virtual PROPERTY_TYPE Type() override { return PROPERTY_TYPE_HALFEDGE_CLUSTER; }
	virtual void Draw(shared_ptr<UniformStruct> pUniform) override;
	virtual void Build(IModelNode* pModel, IPropertyArgs* pPropertyArgs) override;
	virtual void Update(IModelNode* pModel, IPropertyArgs* pPropertyArgs) override;

private:
	void GetClusterColor(IModelNode* pModelNode, IPropertyArgs* pPropertyArgs, vector<vec3>& color);

	shared_ptr<IShader> m_pShader;
	shared_ptr<RenderData> m_pRenderData;
	std::vector<vec3> m_colorMap;
};
}
}

#endif // !HALF_EDGE_RESOLUTION_PROPERTY_H
