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
	virtual void Build(IModelNode* pModel, IPropertyArgs* pPropertyArgs) override;
	virtual void Update(IModelNode* pModel, IPropertyArgs* pPropertyArgs) override;
	virtual void Draw(shared_ptr<UniformStruct> pUniform);
private:
	void SetVBOData(IModelNode* pModelNode);

	shared_ptr<IVertexBuffer> m_pVertexBuffer;
	shared_ptr<ArrayBuffer> m_pTangentBuffer;
	shared_ptr<RenderData> m_pRenderData;
};

}
}