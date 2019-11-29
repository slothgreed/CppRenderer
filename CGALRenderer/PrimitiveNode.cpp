namespace KI
{
PrimitiveNode::PrimitiveNode(shared_ptr<IShader> shader, shared_ptr<DefaultVertexBuffer> buffer)
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
	if (m_pTexture != nullptr)
	{
		m_pTexture->Active(0);
		m_pTexture->Bind();
	}

	m_pShader->Use();
	m_pVertexBuffer->Draw();
	m_pShader->UnUse();

	if (m_pTexture != nullptr)
	{
		m_pTexture->Active(0);
		m_pTexture->UnBind();
	}

	Logger::GLError();
}

void PrimitiveNode::AddTexture(shared_ptr<Texture> texture)
{
	m_pTexture = texture;
}

void PrimitiveNode::Update(void* sender, shared_ptr<EventArgs> args)
{

}

void PrimitiveNode::ShowProperty()
{

}
}
