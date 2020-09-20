namespace KI
{
namespace Gfx
{
RenderBuffer::RenderBuffer()
{
}

RenderBuffer::~RenderBuffer()
{
}


void RenderBuffer::Generate()
{
	if (m_Id != 0)
	{
		Logger::Output(LOG_LEVEL::LOG_LEVEL_ERROR, "Already Generated");
	}

	glGenRenderbuffers(1, &m_Id);
	Logger::GLError();
}

void RenderBuffer::Bind()
{
	glBindRenderbuffer(GL_RENDERBUFFER, m_Id);
	Logger::GLError();
}

void RenderBuffer::UnBind()
{
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	Logger::GLError();
}

void RenderBuffer::Dispose()
{
	if (m_Id != 0)
	{
		glDeleteRenderbuffers(1, &m_Id);
		m_Id = 0;
	}

	Logger::GLError();
}
}
}