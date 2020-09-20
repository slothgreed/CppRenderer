namespace KI
{
namespace ShaderLib
{
UniformMaterial::UniformMaterial()
	: UniformBuffer(MATERIAL_DATA_LOCATION)
{

}

UniformMaterial::~UniformMaterial()
{

}
void UniformMaterial::Set(const MaterialData& data)
{
	m_data = data;
}
void UniformMaterial::Bind()
{
	if (m_Id == 0)
	{
		Logger::Output(LOG_LEVEL::LOG_LEVEL_ERROR, "not Generated");
		assert(0);
		return;
	}

	glBindBuffer(GL_UNIFORM_BUFFER, m_Id);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(MaterialData), &m_data, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	Logger::GLError();

	UniformBuffer::Bind();
}

}
}