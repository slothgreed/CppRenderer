namespace KI
{
namespace Gfx
{
void GLObject::Begin()
{
	if (m_Id == 0)
	{
		assert(0);
	}

	Bind();

	m_modifing = true;
}

void GLObject::End()
{
	UnBind();

	m_modifing = false;
}
}
}