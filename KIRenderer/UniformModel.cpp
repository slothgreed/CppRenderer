namespace KI
{
namespace Renderer
{
UniformModel::UniformModel()
	:UniformBuffer(MODEL_DATA_LOCATION)
{

}

UniformModel::~UniformModel()
{

}

void UniformModel::Set(const ModelData& data)
{
	if (m_Id == 0)
	{
		Logger::Output(LOG_LEVEL::ERROR, "not Generated");
		assert(0);
		return;
	}

	glBindBuffer(GL_UNIFORM_BUFFER, m_Id);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(ModelData), &data, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	Logger::GLError();
}

}
}