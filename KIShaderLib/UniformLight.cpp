namespace KI
{
namespace ShaderLib
{
UniformLight::UniformLight()
	:UniformBuffer(LIGHT_DATA_LOCATION)
{

}

UniformLight::~UniformLight()
{

}

void UniformLight::Set(const LightData& data)
{
	if (m_Id == 0)
	{
		Logger::Output(LOG_LEVEL::LOG_LEVEL_ERROR, "not Generated");
		assert(0);
		return;
	}

	glBindBuffer(GL_UNIFORM_BUFFER, m_Id);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(LightData), &data, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	Logger::GLError();
}

}
}