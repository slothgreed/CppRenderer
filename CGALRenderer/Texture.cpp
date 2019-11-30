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
	if (m_Id == 0)
	{
		assert(0);
	}

	glBindTexture(GL_TEXTURE_2D, m_Id);
	Logger::GLError();
}

void Texture::UnBind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	Logger::GLError();
}

void Texture::Active(GLint active) 
{
	glActiveTexture(active);
	Logger::GLError();
}
void Texture::Set(const TextureData& data)
{
	Bind();
	glTexImage2D(
		data.target, 
		data.level,
		data.internalformat,
		data.width,
		data.height,
		data.border, 
		data.format,
		data.type,
		data.pixels
	);
	UnBind();

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
