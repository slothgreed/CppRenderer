#ifndef HALF_EDGE_RESOLUTION_PROPERTY_H
#define HALF_EDGE_RESOLUTION_PROPERTY_H

namespace KI
{
namespace RenderModel
{

class DLL_EXPORT HalfEdgeResolutionPropertyArgs : public IRenderModelPropertyArgs
{
	friend class HalfEdgeResolutionProperty;
public:
	HalfEdgeResolutionPropertyArgs() :m_level(0) {};
	HalfEdgeResolutionPropertyArgs(int level) :m_level(level) {};
	~HalfEdgeResolutionPropertyArgs() {};
	virtual PROPERTY_TYPE PropertyType() override { return PROPERTY_TYPE_RESOLUTION; }
	int Level() { return m_level; }
private:
	int m_level;
};

class DLL_EXPORT HalfEdgeResolutionProperty : public IRenderModelProperty
{
public:
	HalfEdgeResolutionProperty();
	~HalfEdgeResolutionProperty() {};

	virtual PROPERTY_TYPE PropertyType() override { return PROPERTY_TYPE_RESOLUTION; }
	virtual void Draw(shared_ptr<UniformStruct> pUniform) override;
	virtual void Build(IModelNode* pModel, IPropertyArgs* pPropertyArgs) override;
	virtual void Update(IModelNode* pModel, IPropertyArgs* pPropertyArgs) override;
	virtual void ShowUI() override;
private:
	void SetModel(IModelNode* pModelNode);

	struct UI
	{
		UI() :level(0) {}
		int level;
	};

	static HalfEdgeResolutionPropertyArgs& DefaultArgs();
	void GetClusterColor(IPropertyArgs* pPropertyArgs, vector<vec3>& color);

	UI m_ui;
	shared_ptr<HalfEdgeModel> m_pModel;
	shared_ptr<IShader> m_pShader;
	shared_ptr<RenderData> m_pRenderData;
	std::vector<vec3> m_colorMap;

};
}
}

#endif // !HALF_EDGE_RESOLUTION_PROPERTY_H
