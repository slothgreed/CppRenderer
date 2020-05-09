#ifndef PRIMITIVE_NODE_H
#define PRIMITIVE_NODE_H
namespace KI
{
class PrimitiveNode : public IModelNode
{
public:
	PrimitiveNode(shared_ptr<RenderData> pRenderData);
	PrimitiveNode(shared_ptr<PrimitiveModel> pPrimitive);

	~PrimitiveNode();

	virtual void Draw();
	virtual void Update(void* sender, IEventArgs* args);
	shared_ptr<IShaderPass> GetShaderPass() { return m_pShaderPass; }
	shared_ptr<DefaultVertexBuffer> GetVertexBuffer();
	IndexBuffer* GetIndexBuffer();
	void SetRenderData();
	void SetState(shared_ptr<IGLState> pState) { m_pState = pState; };
	virtual void AddPartSelect(TOPOLOGY_TYPE type, int first, int count);

private:
	string m_name;
	shared_ptr<RenderData> m_pRenderData;
	shared_ptr<IShaderPass> m_pShaderPass;
	shared_ptr<IGLState> m_pState;
};
}

#endif PRIMITIVE_NODE_H