namespace KI
{
namespace Renderer
{

IMaterial::IMaterial()
{
	m_bReCompileShader = true;
	m_pUniform = make_shared<UniformSet>();
}

void IMaterial::SetShader(shared_ptr<IShader> pShader)
{
	m_pShader = pShader;
	m_bReCompileShader = false;
}

void IMaterial::Bind()
{
	if (m_pShader == nullptr)
	{
		assert(0);
	}

	if (m_bReCompileShader == true)
	{
		assert(0);
	}

	m_pShader->Bind(m_pUniform);
}

void IMaterial::UnBind()
{
	m_pShader->Bind(m_pUniform);

}
}
}