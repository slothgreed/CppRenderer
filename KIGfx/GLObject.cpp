namespace KI
{
namespace Gfx
{
void IGLObject::Begin()
{
	if (m_Id == 0)
	{
		assert(0);
	}

	Bind();

	m_modifing = true;
}

void IGLObject::End()
{
	UnBind();

	m_modifing = false;
}
}
}