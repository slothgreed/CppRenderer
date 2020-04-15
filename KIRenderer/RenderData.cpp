namespace KI
{
namespace Renderer
{
RenderData::RenderData(GLuint primitiveType, shared_ptr<IVertexBuffer> pVertexBuffer, shared_ptr<IndexBuffer> pIndexBuffer)
{
	m_pPrimitiveType = primitiveType;
	m_pVertexBuffer = pVertexBuffer;
	m_pIndexBuffer = pIndexBuffer;
}

RenderData::~RenderData()
{
}

};
}
