namespace KI
{
namespace Gfx
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

	SetSize(width, height);
}

void SymbolicRenderTarget::Dispose()
{

}

bool SymbolicRenderTarget::GetPixels(ReadPixelArgs& args, RENDER_TEXTURE_TYPE type, FRAMEBUFFER_ATTACHMENT index)
{
	if (type != RENDER_TEXTURE_TYPE::RENDER_COLOR_TEXTURE) {
		assert(0);
		return false;
	}

	if (index >= ColorTextureNum())
	{
		assert(0);
		return false;
	}

	glReadBuffer(m_drawBuffer);
	args.format = GL_RGB;
	args.type = GL_UNSIGNED_BYTE;

	return IRenderTarget::GetPixels(args);
}
}
}
