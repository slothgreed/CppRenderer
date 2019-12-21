
namespace KI
{
PrimitiveNode::PrimitiveNode(shared_ptr<IShader> shader, shared_ptr<DefaultVertexBuffer> buffer)
{
	m_name = "Primitive";
	m_pMaterial = make_shared<DefaultMaterial>();
	m_pMaterial->SetVertexBuffer(buffer);
	m_pMaterial->CompileShader();
}

PrimitiveNode::~PrimitiveNode()
{
}

void PrimitiveNode::Draw()
{
	m_pMaterial->Draw();

	Logger::GLError();
}


void PrimitiveNode::Update(void* sender, shared_ptr<EventArgs> args)
{

}

void PrimitiveNode::ShowProperty()
{

}
}


