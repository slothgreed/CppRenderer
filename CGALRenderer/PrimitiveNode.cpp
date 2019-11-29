namespace KI
{
PrimitiveNode::PrimitiveNode(shared_ptr<IShader> shader, shared_ptr<VertexBuffer> buffer)
{
	m_name = "Primitive";
	m_pShader = shader;
	m_pVertexBuffer = buffer;
}

PrimitiveNode::~PrimitiveNode()
{
}

void PrimitiveNode::Draw()
{
	m_pShader->Use();
	m_pVertexBuffer->Draw();
	m_pShader->UnUse();
	Logger::GLError();
}

void PrimitiveNode::Update(void* sender, shared_ptr<EventArgs> args)
{

}

void PrimitiveNode::ShowProperty()
{

}
}
