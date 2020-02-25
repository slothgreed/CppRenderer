
namespace KI
{
PrimitiveNode::PrimitiveNode(shared_ptr<IShader> shader, shared_ptr<DefaultVertexBuffer> buffer)
{
	m_name = "Primitive";
	m_pVertexBuffer = buffer;
	m_pMaterial = make_shared<DefaultMaterial>();
}

PrimitiveNode::~PrimitiveNode()
{
}

void PrimitiveNode::Draw()
{
	m_pMaterial->Draw(m_pVertexBuffer.get());

	Logger::GLError();
}


void PrimitiveNode::Update(void* sender, shared_ptr<EventArgs> args)
{

}

void PrimitiveNode::ShowProperty()
{

}
}
