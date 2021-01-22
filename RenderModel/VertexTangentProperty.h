namespace KI
{
namespace RenderModel
{

class VertexTangentProperty : public IModelProperty
{
public:
	VertexTangentProperty();
	~VertexTangentProperty();

	virtual PROPERTY_TYPE Type() override { return PROPERTY_TYPE_VERTEX_TANGENT; }
	virtual void Build(IModelNode* pModel, IPropertyArgs* pPropertyArgs) override;
	virtual void Update(IModelNode* pModel, IPropertyArgs* pPropertyArgs) override;
	virtual void Draw(shared_ptr<UniformStruct> pUniform);
private:
	void SetVBOData(IModelNode* pModelNode);

	shared_ptr<IVertexBuffer> m_pVertexBuffer;
	shared_ptr<ArrayBuffer> m_pTangentBuffer;
	shared_ptr<TangentVisualizeShading> m_pShading;
	shared_ptr<RenderData> m_pRenderData;
};

}
}