namespace KI
{
namespace Renderer
{
UniformLight::UniformLight()
{
	m_Id = 0;
}

UniformLight::~UniformLight()
{
}


void UniformLight::Generate()
{
	glGenBuffers(1, &m_Id);
}

void UniformLight::Set(const LightData& data)
{
	if (m_Id == 0)
	{
		Logger::Output(LOG_LEVEL::ERROR, "not Generated");
		assert(0);
		return;
	}

	glBindBuffer(GL_UNIFORM_BUFFER, m_Id);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(LightData), &data, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	Logger::GLError();
}

void UniformLight::Set(ILight* pLight)
{
	LightData light;
	if (pLight->Type() == LIGHT_TYPE_DIRECTION)
	{
		DirectionLight* pDirection = (DirectionLight*)pLight;
		light.direction = vec4(pDirection->Direction(), 1.0);
		light.ambient = pDirection->Ambient();
		light.diffuse = pDirection->Diffuse();
		light.specular = pDirection->Specular();
	}

	Set(light);
}
void UniformLight::Bind()
{
	if (m_Id == 0)
	{
		Logger::Output(LOG_LEVEL::ERROR, "not Generated");
		assert(0);
		return;
	}

	glBindBufferBase(GL_UNIFORM_BUFFER, LIGHT_DATA_LOCATION, m_Id);
	Logger::GLError();
}

void UniformLight::UnBind()
{
	glBindBufferBase(GL_UNIFORM_BUFFER, LIGHT_DATA_LOCATION, 0);
	Logger::GLError();
}

void UniformLight::Dispose()
{
	if (m_Id != 0)
	{
		glDeleteBuffers(1, &m_Id);
		m_Id = 0;
	}
}
}
}