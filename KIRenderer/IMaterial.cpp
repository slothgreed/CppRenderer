namespace KI
{
namespace Renderer
{

void IMaterial::Draw(IVertexBuffer* pVertexBuffer)
{
	if (pVertexBuffer == nullptr)
	{
		assert(0);
	}

	m_pShader = CompileShader(pVertexBuffer);

	m_pShader->Use();
	Bind();
	pVertexBuffer->Draw();
	UnBind();
	m_pShader->UnUse();
}
}
}