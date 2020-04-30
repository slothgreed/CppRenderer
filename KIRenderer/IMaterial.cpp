namespace KI
{
namespace Renderer
{

IMaterial::IMaterial()
{
	m_bReCompileShader = true;
}

void IMaterial::SetShader(shared_ptr<IShader> pShader)
{
	m_pShader = pShader;
	m_bReCompileShader = false;
}
}
}