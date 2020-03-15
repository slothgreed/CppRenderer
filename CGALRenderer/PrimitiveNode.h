#ifndef PRIMITIVE_NODE_H
#define PRIMITIVE_NODE_H
namespace KI
{
class PrimitiveNode : public IModelNode
{
public:
	PrimitiveNode(shared_ptr<DefaultVertexBuffer> buffer);
	~PrimitiveNode();

	virtual void Draw();
	virtual void Pick(const vec3& direction, PickResult& result) override {};
	virtual void ShowProperty();
	virtual void Update(void* sender, IEventArgs* args);
	DefaultMaterial* GetMaterial() { return m_pMaterial.get(); }
	DefaultVertexBuffer* GetVertexBuffer() { return m_pVertexBuffer.get(); }
	void SetState(shared_ptr<IGLState> pState) { m_pState = pState; };
		
private:
	string m_name;
	shared_ptr<DefaultMaterial> m_pMaterial;
	shared_ptr<DefaultVertexBuffer> m_pVertexBuffer;
	shared_ptr<IGLState> m_pState;
};
}

#endif PRIMITIVE_NODE_H