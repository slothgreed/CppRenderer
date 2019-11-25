namespace KI
{
Texture::Texture()
{
}

Texture::~Texture()
{
}

void Texture::Generate()
{
	if (m_Id != 0)
	{
		Logger::Output(LOG_LEVEL::ERROR, "Already Generated");
	}

	glGenTextures(1, &m_Id);
	Logger::GLError();
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, m_Id);
	Logger::GLError();
}

void Texture::UnBind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	Logger::GLError();
}

void Texture::Dispose()
{
	if (m_Id != 0)
	{
		glDeleteTextures(1, &m_Id);
		m_Id = 0;
	}

	Logger::GLError();
}
}
