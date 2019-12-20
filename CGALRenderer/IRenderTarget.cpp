namespace KI
{
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

void IRenderTarget::Clear()
{
	if (Modifing() == false)
	{
		assert(0);
	}

	glClearColor(m_pClearColor.r, m_pClearColor.g, m_pClearColor.b, m_pClearColor.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
}