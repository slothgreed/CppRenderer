#ifndef PRIMITIVE_NODE_H
#define PRIMITIVE_NODE_H
namespace KI
{
namespace RenderModel
{
class DLL_EXPORT PrimitiveNode : public IRenderModelNode
{
public:
	PrimitiveNode(shared_ptr<RenderData> pRenderData);
	PrimitiveNode(shared_ptr<PrimitiveModel> pPrimitive);
	PrimitiveNode(shared_ptr<PrimitiveModel> pPrimitive, shared_ptr<IShading> pShading);

	~PrimitiveNode();

	virtual void Update(void* sender, IEventArgs* args);
	shared_ptr<IShading> GetShading() { return m_pShading; }
	shared_ptr<DefaultVertexBuffer> GetVertexBuffer();
	IndexBuffer* GetIndexBuffer();
	void SetRenderData();
	virtual void AddSelect(PICK_TYPE type, shared_ptr<IShading> pShading, int index, int first, int count);

private:
	string m_name;
	shared_ptr<IShading> m_pShading;
};
}
}
#endif PRIMITIVE_NODE_H