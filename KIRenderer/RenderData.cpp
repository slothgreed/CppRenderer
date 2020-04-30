namespace KI
{
namespace Renderer
{
RenderData::RenderData(GLuint primitiveType, shared_ptr<IVertexBuffer> pVertexBuffer, shared_ptr<IndexBuffer> pIndexBuffer)
{
	SetGeometryData(primitiveType, pVertexBuffer, pIndexBuffer);
}

RenderData::~RenderData()
{
}

void RenderData::SetMaterial(shared_ptr<IMaterial> pMaterial)
{
	m_pMaterial = pMaterial;
}

void RenderData::SetGeometryData(GLuint primitiveType, shared_ptr<IVertexBuffer> pVertexBuffer, shared_ptr<IndexBuffer> pIndexBuffer)
{
	m_pPrimitiveType = primitiveType;
	m_pVertexBuffer = pVertexBuffer;
	m_pIndexBuffer = pIndexBuffer;
}

void RenderData::Draw(shared_ptr<IShader> pShader)
{
	pShader->Use();

	if (m_pMaterial != nullptr)
	{
		m_pMaterial->Bind();
	}


	if (m_pIndexBuffer == nullptr)
	{
		m_pVertexBuffer->Draw(m_pPrimitiveType);
	}
	else
	{
		m_pVertexBuffer->Draw(m_pPrimitiveType, m_pIndexBuffer.get());
	}

	if (m_pMaterial != nullptr)
	{
		m_pMaterial->UnBind();
	}

	pShader->UnUse();
}

void RenderData::Draw()
{
	if (m_pVertexBuffer == nullptr ||
		m_pMaterial == nullptr)
	{
		assert(0);
		return;
	}

	if (m_pMaterial->NeedReCompileShader())
	{
		m_pMaterial->CompileShader(GetVertexBuffer().get());
	}

	Draw(m_pMaterial->GetShader());

}

};
}
