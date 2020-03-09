namespace KI
{
namespace Gfx
{
UniformBuffer::UniformBuffer(GLuint dataLocation)
{
	m_Id = 0;
	m_dataLocation = dataLocation;
}

UniformBuffer::~UniformBuffer()
{
}

void UniformBuffer::Generate()
{
	if (m_Id != 0)
	{
		Logger::Output(LOG_LEVEL::ERROR, "Already Created");
		assert(0);
		return;
	}

	glGenBuffers(1, &m_Id);

}

void UniformBuffer::Bind()
{
	if (m_Id == 0)
	{
		Logger::Output(LOG_LEVEL::ERROR, "not Generated");
		assert(0);
		return;
	}

	glBindBufferBase(GL_UNIFORM_BUFFER, m_dataLocation, m_Id);
	Logger::GLError();
}

void UniformBuffer::UnBind()
{
	glBindBufferBase(GL_UNIFORM_BUFFER, m_dataLocation, 0);
	Logger::GLError();
}

void UniformBuffer::Dispose()
{
	if (m_Id != 0)
	{
		glDeleteBuffers(1, &m_Id);
		m_Id = 0;
	}
}
}
}