#ifndef HALF_EDGE_RESOLUTION_PROPERTY_H
#define HALF_EDGE_RESOLUTION_PROPERTY_H

namespace KI
{
namespace RenderModel
{

class DLL_EXPORT ResolutionParameterPropertyArgs : public IRenderModelPropertyArgs
{

	friend class ResolutionParameterProperty;
public:
	enum RESOLUTION_PARAMETER
	{
		COLOR	 = 0x0,
		TANGENT = 0x1,
		NORMAL = 0x2,
		AREA = 0x4
	};
	ResolutionParameterPropertyArgs() :m_level(0), m_Type(COLOR) {};
	ResolutionParameterPropertyArgs(int level) :m_level(level), m_Type(COLOR) {};
	ResolutionParameterPropertyArgs(int level, RESOLUTION_PARAMETER type) :m_level(level),m_Type(type) {};

	~ResolutionParameterPropertyArgs() {};
	virtual PROPERTY_TYPE PropertyType() override { return PROPERTY_TYPE_RESOLUTION; }
	int Level() { return m_level; }
	RESOLUTION_PARAMETER ParameterType() { return m_Type; }
private:
	int m_level;
	RESOLUTION_PARAMETER m_Type;
};

class DLL_EXPORT ResolutionParameterProperty : public IRenderModelProperty
{
public:
	ResolutionParameterProperty();
	~ResolutionParameterProperty() {};

	virtual PROPERTY_TYPE PropertyType() override { return PROPERTY_TYPE_RESOLUTION; }
	virtual void Draw(shared_ptr<UniformStruct> pUniform) override;
	virtual void BuildCore(IModelNode* pModel, IPropertyArgs* pPropertyArgs) override;
	virtual void Update(IModelNode* pModel, IPropertyArgs* pPropertyArgs) override;
	virtual void InitializeUI() override;
	virtual void ShowUI() override;
private:
	void BuildColor(IModelNode* pModelNode, ResolutionParameterPropertyArgs* pPropertyArgs);
	void UpdateColor(IModelNode* pModelNode, ResolutionParameterPropertyArgs* pPropertyArgs);
	void BuildTangent(IModelNode* pModelNode, ResolutionParameterPropertyArgs* pPropertyArgs);
	void UpdateTangent(IModelNode* pModelNode, ResolutionParameterPropertyArgs* pPropertyArgs);
	void InitializeColorMap(int size);
	void SetModel(IModelNode* pModelNode);

	struct UI
	{
		UI(){}
		SliderIntUI resolution;
	};

	static ResolutionParameterPropertyArgs& DefaultArgs();
	void GetClusterColor(ResolutionParameterPropertyArgs* pPropertyArgs, vector<vec3>& color);
	UI m_ui;
	shared_ptr<HalfEdgeModel> m_pModel;
	shared_ptr<IShader> m_pShader;
	shared_ptr<RenderData> m_pRenderData;
	shared_ptr<ArrayBuffer> m_pTangentBuffer;
	std::vector<vec3> m_colorMap;

};
}
}

#endif // !HALF_EDGE_RESOLUTION_PROPERTY_H
