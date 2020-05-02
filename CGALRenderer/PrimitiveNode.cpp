
namespace KI
{
PrimitiveNode::PrimitiveNode(shared_ptr<RenderData> pRenderData)
{
	m_name = "Primitive";
	m_pRenderData = pRenderData;
	if (pRenderData->GetMaterial() == nullptr)
	{
		m_pRenderData->SetMaterial(make_shared<DefaultMaterial>());
	}
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

	m_pRenderData->Draw();

	if (m_pState != nullptr)
	{
		m_pState->UnBind();
	}

	Logger::GLError();
}

IndexBuffer* PrimitiveNode::GetIndexBuffer()
{
	if (m_pRenderData == nullptr)
	{
		assert(0);
		return nullptr;
	}

	return m_pRenderData->GetIndexBuffer().get();
}

shared_ptr<DefaultVertexBuffer> PrimitiveNode::GetVertexBuffer()
{
	if (m_pRenderData == nullptr)
	{
		assert(0);
		return nullptr;
	}

	if (m_pRenderData->GetVertexBuffer()->Type() != VERTEX_BUFFER_TYPE_DEFAULT)
	{
		assert(0);
		return nullptr;
	}



	return static_pointer_cast<DefaultVertexBuffer>(m_pRenderData->GetVertexBuffer());
}

void PrimitiveNode::Update(void* sender, IEventArgs* args)
{

}

}
