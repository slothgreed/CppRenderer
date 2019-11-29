#ifndef PRIMITIVE_NODE_H
#define PRIMITIVE_NODE_H
namespace KI
{
class PrimitiveNode : public IModelNode
{
public:
	PrimitiveNode(shared_ptr<IShader> shader, shared_ptr<DefaultVertexBuffer> buffer);
	~PrimitiveNode();

	virtual void Draw();
	virtual void ShowProperty();
	virtual void Update(void* sender, shared_ptr<EventArgs> args);
	virtual void AddTexture(shared_ptr<Texture> texture);
private:
	string m_name;
	shared_ptr<Texture> m_pTexture;
	shared_ptr<IShader> m_pShader;
	shared_ptr<DefaultVertexBuffer> m_pVertexBuffer;
};
}

#endif PRIMITIVE_NODE_H