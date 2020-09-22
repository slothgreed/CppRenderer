namespace KI
{
namespace Gfx
{
IRenderTarget::IRenderTarget()
{
	m_pClearColor = vec4(1);
	m_size = vec4(0);
}

IRenderTarget::~IRenderTarget()
{
}

void IRenderTarget::Begin()
{
	Bind();

	m_modifing = true;
}

void IRenderTarget::End()
{
	UnBind();

	m_modifing = false;
}

void IRenderTarget::Clear(GLbitfield clear)
{
	if (clear & GL_COLOR_BUFFER_BIT ||
		clear & GL_DEPTH_BUFFER_BIT) {
	}
	else
	{
		assert(0);
	}

	if (Modifing() == false)
	{
		assert(0);
	}

	glClearColor(m_pClearColor.r, m_pClearColor.g, m_pClearColor.b, m_pClearColor.a);
	glClear(clear);
}

}
}