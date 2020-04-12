#ifndef PRIMITIVE_NODE_H
#define PRIMITIVE_NODE_H
namespace KI
{
class PrimitiveNode : public IModelNode
{
public:
	PrimitiveNode(shared_ptr<DefaultVertexBuffer> pVertexBuffer, shared_ptr<IndexBuffer> pIndexBuffer);
	PrimitiveNode(shared_ptr<DefaultVertexBuffer> pVertexBuffer, shared_ptr<IndexBuffer> pIndexBuffer, shared_ptr<IMaterial> pMaterial);
	PrimitiveNode(shared_ptr<DefaultVertexBuffer> pVertexBuffer);
	PrimitiveNode(shared_ptr<DefaultVertexBuffer> pVertexBuffer, shared_ptr<IMaterial> pMaterial);
	~PrimitiveNode();

	virtual void Draw();
	virtual void Update(void* sender, IEventArgs* args);
	shared_ptr<IMaterial> GetMaterial() { return m_pMaterial; }
	shared_ptr<DefaultVertexBuffer> GetVertexBuffer() { return m_pVertexBuffer; }
	IndexBuffer* GetIndexBuffer();
	void SetState(shared_ptr<IGLState> pState) { m_pState = pState; };
		
private:
	string m_name;
	shared_ptr<IMaterial> m_pMaterial;
	shared_ptr<DefaultVertexBuffer> m_pVertexBuffer;
	shared_ptr<IndexBuffer> m_pIndexBuffer;
	shared_ptr<IGLState> m_pState;
};
}

#endif PRIMITIVE_NODE_H