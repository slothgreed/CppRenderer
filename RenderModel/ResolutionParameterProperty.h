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
		NONE	= 0x0,
		COLOR	= 0x1,
		TANGENT = 0x2,
		QUAD	= 0x4,
		PARAM	= 0x8
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
	void BuildParameter(IModelNode* pModelNode, ResolutionParameterPropertyArgs* pPropertyArgs);
	void UpdateParameter(IModelNode* pModelNode, ResolutionParameterPropertyArgs* pPropertyArgs);
	void InitializeColorMap(int size);
	void SetModel(IModelNode* pModelNode);

	struct UI
	{
		UI(){}
		SliderIntUI resolution;
		CheckBoxUI color;
		CheckBoxUI tangent;
		CheckBoxUI quad;
		CheckBoxUI parameterization;
	};

	struct GPUBuffer 
	{
		shared_ptr<DefaultVertexBuffer> colorVBO;
		shared_ptr<VertexBuffer> tangentVBO;
		shared_ptr<VertexBuffer> quadVBO;
		shared_ptr<VertexBuffer> paramVBO;

		shared_ptr<ArrayBuffer> positionBuffer;	// per level.
		shared_ptr<ArrayBuffer> normalBuffer;
		shared_ptr<ArrayBuffer> tangentBuffer;
		shared_ptr<ArrayBuffer> quadBuffer;

		shared_ptr<RenderData> colorData;
		shared_ptr<RenderData> tangentData;
		shared_ptr<RenderData> quadData;
		shared_ptr<RenderData> paramData;

	};
	static ResolutionParameterPropertyArgs& DefaultArgs();
	void GetClusterColor(int level, vector<vec3>& color);
	UI m_ui;
	shared_ptr<HalfEdgeModel> m_pModel;
	std::vector<vec3> m_colorMap;
	GPUBuffer m_buffers;

};
}
}

#endif // !HALF_EDGE_RESOLUTION_PROPERTY_H
