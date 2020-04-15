namespace KI
{
namespace Renderer
{
RenderData::RenderData(GLuint primitiveType, shared_ptr<IVertexBuffer> pVertexBuffer, shared_ptr<IndexBuffer> pIndexBuffer)
{
	Set(primitiveType, pVertexBuffer, pIndexBuffer);
}

RenderData::~RenderData()
{
}

void RenderData::Set(GLuint primitiveType, shared_ptr<IVertexBuffer> pVertexBuffer, shared_ptr<IndexBuffer> pIndexBuffer)
{
	m_pPrimitiveType = primitiveType;
	m_pVertexBuffer = pVertexBuffer;
	m_pIndexBuffer = pIndexBuffer;
}
void RenderData::Draw()
{
	if (m_pVertexBuffer == nullptr)
	{
		assert(0);
		return;
	}

	if (m_pIndexBuffer == nullptr)
	{
		m_pVertexBuffer->Draw(m_pPrimitiveType);
	}
	else
	{
		m_pVertexBuffer->Draw(m_pPrimitiveType, m_pIndexBuffer.get());
	}
}

};
}
