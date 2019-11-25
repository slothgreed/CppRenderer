
namespace KI
{

Sampler::Sampler()
{
}

Sampler::~Sampler()
{
}

void Sampler::Generate()
{
	if (m_Id != 0)
	{
		Logger::Output(LOG_LEVEL::ERROR, "Already Generated");
	}

	glCreateSamplers(1, &m_Id);
	Logger::GLError();
}

void Sampler::Bind()
{
	glBindSampler(1, m_Id);
	Logger::GLError();
}

void Sampler::UnBind()
{
	glBindSampler(1, 0);
	Logger::GLError();
}

void Sampler::Dispose()
{
	if (m_Id != 0)
	{
		glDeleteSamplers(1, &m_Id);
		m_Id = 0;
	}

	Logger::GLError();
}
}
