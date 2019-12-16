namespace KI
{


SymbolicRenderTarget::SymbolicRenderTarget(GLenum drawBuffer)
{
	m_drawBuffer = drawBuffer;
}

SymbolicRenderTarget::~SymbolicRenderTarget()
{

}


void SymbolicRenderTarget::Bind()
{
	glDrawBuffer(m_drawBuffer);
}

void SymbolicRenderTarget::UnBind()
{
	glDrawBuffer(GL_BACK);
}

void SymbolicRenderTarget::Resize(int width, int height)
{
	if (m_drawBuffer == GL_BACK)
	{
		glViewport(0, 0, width, height);
	}
}

void SymbolicRenderTarget::Dispose()
{

}


}
