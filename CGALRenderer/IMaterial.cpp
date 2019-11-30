namespace KI
{

void IMaterial::SetVertexBuffer(shared_ptr<IVertexBuffer> vertexBuffer)
{
	m_pVertexBuffer = vertexBuffer;
}

void IMaterial::Draw()
{
	if (m_pShader == nullptr ||
		m_pVertexBuffer == nullptr)
	{
		assert(0);
	}

	Bind();
	m_pShader->Use();
	m_pVertexBuffer->Draw();
	m_pShader->UnUse();
	UnBind();
}
}