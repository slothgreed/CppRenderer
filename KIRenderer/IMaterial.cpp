namespace KI
{
namespace Renderer
{

void IMaterial::Draw(IVertexBuffer* pVertexBuffer, IndexBuffer* pIndexBuffer)
{
	if (pVertexBuffer == nullptr)
	{
		assert(0);
	}

	m_pShader = CompileShader(pVertexBuffer);

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