#ifndef VERTEX_TANGENT_PROPERTY_H
#define VERTEX_TANGENT_PROPERTY_H
namespace KI
{
namespace RenderModel
{
class VertexTangentPropertyArgs : public IRenderModelPropertyArgs
{
public:
	VertexTangentPropertyArgs(int level) :m_level(level) {};
	~VertexTangentPropertyArgs() {};
	virtual PROPERTY_TYPE PropertyType() override { return PROPERTY_TYPE_VERTEX_TANGENT; }

	int Level() { return m_level; };
private:
	int m_level;
};

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
		SliderIntUI level;
	};

	struct GPUBuffer
	{
		shared_ptr<ArrayBuffer> positionBuffer;
		shared_ptr<ArrayBuffer> normalBuffer;
		shared_ptr<ArrayBuffer> tangentBuffer;
	};

	shared_ptr<HalfEdgeModel> GetHalfEdgeModel();
	UI m_ui;
	void SetVBOData(IModelNode* pModelNode, VertexTangentPropertyArgs* pPropertyArgs);
	shared_ptr<VertexBuffer> m_pVertexBuffer;
	GPUBuffer m_ArrayBuffers;
	shared_ptr<RenderData> m_pRenderData;
	shared_ptr<TangentVisualizeShading> m_pShading;
};

}
}

#endif VERTEX_TANGENT_PROPERTY_H
