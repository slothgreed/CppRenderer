#ifndef BVH_PROPERTY_H
#define BVH_PROPERTY_H
namespace KI
{
namespace RenderModel
{
class BVHProperty : public IModelProperty
{
public:
	BVHProperty();
	~BVHProperty();

	virtual PROPERTY_TYPE Type() override { return PROPERTY_TYPE_BVH; }
	virtual void Build(IModelNode* pModel, IPropertyArgs* pPropertyArgs) override;
	virtual void Update(IModelNode* pModel, IPropertyArgs* pPropertyArgs) override;
	virtual void Draw(shared_ptr<UniformStruct> pUniform);
private:
	void SetInstanceBuffer(IModelNode* pModelNode);
	void SetBoxBuffer(shared_ptr<DefaultVertexBuffer> pVertexBuffer, shared_ptr<IndexBuffer> pIndexBuffer);
	shared_ptr<DefaultVertexBuffer> m_pVertexBuffer;
	std::vector<mat4> m_pMatrixBuffer;
	shared_ptr<TangentVisualizeShading> m_pShading;
	shared_ptr<RenderData> m_pRenderData;
};

}
}

#endif BVH_PROPERTY_H
