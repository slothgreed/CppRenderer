namespace KI
{
namespace Renderer
{

IMaterial::IMaterial()
{
	m_bReCompileShader = true;
}
void IMaterial::Draw(IVertexBuffer* pVertexBuffer, IndexBuffer* pIndexBuffer)
{
	if (pVertexBuffer == nullptr)
	{
		assert(0);
	}

	if (m_bReCompileShader == true)
	{
		m_pShader = CompileShader(pVertexBuffer);
		m_bReCompileShader = false;
	}

	m_pShader->Use();
	Bind();
	if (pIndexBuffer == nullptr)
	{
		pVertexBuffer->Draw();
	}
	else
	{
		pVertexBuffer->Draw(pIndexBuffer);
	}
	UnBind();
	m_pShader->UnUse();
}

}
}