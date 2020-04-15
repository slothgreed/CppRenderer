namespace KI
{
namespace Renderer
{

IMaterial::IMaterial()
{
	m_bReCompileShader = true;
}
void IMaterial::Draw(RenderData* pRenderData)
{
	if (pRenderData == nullptr)
	{
		assert(0);
	}

	if (m_bReCompileShader == true)
	{
		m_pShader = CompileShader(pRenderData->GetVertexBuffer().get());
		m_bReCompileShader = false;
	}

	m_pShader->Use();
	Bind();
	pRenderData->Draw();
	UnBind();
	m_pShader->UnUse();
}

}
}