namespace KI
{
namespace RenderModel
{

class VertexTangentProperty : public IRenderModelProperty
{
public:
	VertexTangentProperty();
	~VertexTangentProperty();

	virtual PROPERTY_TYPE PropertyType() override { return PROPERTY_TYPE_VERTEX_TANGENT; }
	virtual void BuildCore(IModelNode* pModel, IPropertyArgs* pPropertyArgs) override;
	virtual void Update(IModelNode* pModel, IPropertyArgs* pPropertyArgs) override;
	virtual void Draw(shared_ptr<UniformStruct> pUniform);
	virtual void InitializeUI();
	virtual void ShowUI();
private:

	struct UI
	{
		SliderFloatUI tangent;
		SliderFloatUI offset;
		ColorPicker4UI color;
	};

	UI m_ui;
	void SetVBOData(IModelNode* pModelNode);
	shared_ptr<IVertexBuffer> m_pVertexBuffer;
	shared_ptr<ArrayBuffer> m_pTangentBuffer;
	shared_ptr<RenderData> m_pRenderData;
	shared_ptr<TangentVisualizeShading> m_pShading;
};

}
}