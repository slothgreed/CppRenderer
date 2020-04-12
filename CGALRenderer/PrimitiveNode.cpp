
namespace KI
{
PrimitiveNode::PrimitiveNode(shared_ptr<DefaultVertexBuffer> pVertexBuffer, shared_ptr<IndexBuffer> pIndexBuffer)
{
	m_name = "Primitive";
	m_pVertexBuffer = pVertexBuffer;
	m_pIndexBuffer = pIndexBuffer;
	m_pMaterial = make_shared<DefaultMaterial>();
}

PrimitiveNode::PrimitiveNode(shared_ptr<DefaultVertexBuffer> pVertexBuffer)
{
	m_name = "Primitive";
	m_pVertexBuffer = pVertexBuffer;
	m_pMaterial = make_shared<DefaultMaterial>();
}

PrimitiveNode::PrimitiveNode(shared_ptr<DefaultVertexBuffer> pVertexBuffer, shared_ptr<IndexBuffer> pIndexBuffer, shared_ptr<IMaterial> pMaterial)
{
	m_name = "Primitive";
	m_pVertexBuffer = pVertexBuffer;
	m_pIndexBuffer = pIndexBuffer;
	m_pMaterial = pMaterial;
}

PrimitiveNode::PrimitiveNode(shared_ptr<DefaultVertexBuffer> pVertexBuffer, shared_ptr<IMaterial> pMaterial)
{
	m_name = "Primitive";
	m_pVertexBuffer = pVertexBuffer;
	m_pMaterial = pMaterial;
}

PrimitiveNode::~PrimitiveNode()
{
}

void PrimitiveNode::Draw()
{
	if (m_pState != nullptr)
	{
		m_pState->Bind();
	}

	m_pMaterial->Draw(m_pVertexBuffer.get(), m_pIndexBuffer.get());

	if (m_pState != nullptr)
	{
		m_pState->UnBind();
	}

	Logger::GLError();
}

IndexBuffer* PrimitiveNode::GetIndexBuffer()
{
	if (m_pIndexBuffer == nullptr)
	{
		assert(0);
		return nullptr;
	}

	return m_pIndexBuffer.get();
}

void PrimitiveNode::Update(void* sender, IEventArgs* args)
{

}

}
