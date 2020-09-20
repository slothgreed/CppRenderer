
namespace KI
{
namespace Gfx
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
		Logger::Output(LOG_LEVEL::LOG_LEVEL_ERROR, "Already Generated");
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

void Sampler::Set(const SamplerData& samplerData)
{
	m_samplerData = samplerData;
	if (samplerData.MIN_FILTER != GL_NONE)
	{
		glSamplerParameteri(m_Id, GL_TEXTURE_MIN_FILTER, samplerData.MIN_FILTER);
	}

	if (samplerData.MAG_FILTER != GL_NONE)
	{
		glSamplerParameteri(m_Id, GL_TEXTURE_MAG_FILTER, samplerData.MAG_FILTER);
	}

	if (samplerData.WRAP_S != GL_NONE)
	{
		glSamplerParameteri(m_Id, GL_TEXTURE_WRAP_S, samplerData.WRAP_S);
	}

	if (samplerData.WRAP_R != GL_NONE)
	{
		glSamplerParameteri(m_Id, GL_TEXTURE_WRAP_R, samplerData.WRAP_R);
	}

	if (samplerData.WRAP_T != GL_NONE)
	{
		glSamplerParameteri(m_Id, GL_TEXTURE_WRAP_T, samplerData.WRAP_T);
	}
}

bool Sampler::Compare(const SamplerData& samplerData)
{
	int result = memcmp(&samplerData, &m_samplerData, sizeof(SamplerData));
	if (result == 0)
	{
		return true;
	}

	return false;
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
}