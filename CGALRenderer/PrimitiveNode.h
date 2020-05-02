#ifndef PRIMITIVE_NODE_H
#define PRIMITIVE_NODE_H
namespace KI
{
class PrimitiveNode : public IModelNode
{
public:
	PrimitiveNode(shared_ptr<RenderData> pRenderData);
	~PrimitiveNode();

	virtual void Draw();
	virtual void Update(void* sender, IEventArgs* args);
	shared_ptr<IMaterial> GetMaterial() { return m_pMaterial; }
	shared_ptr<DefaultVertexBuffer> GetVertexBuffer();
	IndexBuffer* GetIndexBuffer();
	void SetState(shared_ptr<IGLState> pState) { m_pState = pState; };
		
private:
	string m_name;
	shared_ptr<RenderData> m_pRenderData;
	shared_ptr<IMaterial> m_pMaterial;
	shared_ptr<IGLState> m_pState;
};
}

#endif PRIMITIVE_NODE_H