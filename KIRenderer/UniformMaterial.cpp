namespace KI
{
namespace Renderer
{
UniformMaterial::UniformMaterial()
	:UniformBuffer(SHADING_DATA_LOCATION)
{

}

UniformMaterial::~UniformMaterial()
{

}

void UniformMaterial::Set(const MaterialData& data)
{
	if (m_Id == 0)
	{
		Logger::Output(LOG_LEVEL::ERROR, "not Generated");
		assert(0);
		return;
	}

	glBindBuffer(GL_UNIFORM_BUFFER, m_Id);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(MaterialData), &data, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	Logger::GLError();
}

}
}