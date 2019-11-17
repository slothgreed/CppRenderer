#ifndef PRIMITIVE_NODE_H
#define PRIMITIVE_NODE_H
#include "IModelNode.h"
class PrimitiveNode : public IModelNode
{
public:
	PrimitiveNode(shared_ptr<IShader> shader, shared_ptr<VertexBuffer> buffer);
	~PrimitiveNode();

	virtual void Draw();
	virtual void ShowProperty();
	virtual void Update(void* sender, shared_ptr<EventArgs> args);

private:
	string m_name;
	shared_ptr<IShader> m_pShader;
	shared_ptr<VertexBuffer> m_pVertexBuffer;
};


#endif PRIMITIVE_NODE_H