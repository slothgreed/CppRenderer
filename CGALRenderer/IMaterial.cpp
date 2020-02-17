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
	
	m_pShader->Use();
	Bind();
	m_pVertexBuffer->Draw();
	UnBind();
	m_pShader->UnUse();
}

void IMaterial::Draw(IVertexBuffer* pVertexBuffer)
{
	if (m_pShader == nullptr ||
		pVertexBuffer == nullptr)
	{
		assert(0);
	}

	m_pShader->Use();
	Bind();
	pVertexBuffer->Draw();
	UnBind();
	m_pShader->UnUse();
}

}