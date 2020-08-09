namespace KI
{
namespace ShaderLib
{
UniformModel::UniformModel()
	:UniformBuffer(MODEL_DATA_LOCATION)
{

}

UniformModel::~UniformModel()
{

}

void UniformModel::SetViewMatrix(const mat4x4& viewMatrix)
{
	m_viewMatrix = viewMatrix;
}
void UniformModel::SetModelMatrix(const mat4x4& data)
{
	m_ModelData.modelViewMatrix = m_viewMatrix * data;
	m_ModelData.modelMatrix = data;
	m_ModelData.normalMatrix = glm::inverse(glm::transpose(m_ModelData.modelMatrix));
}

void UniformModel::SetObjectId(int id)
{
	m_ModelData.objectId = id;
}
void UniformModel::Bind()
{
	if (m_Id == 0)
	{
		Logger::Output(LOG_LEVEL::ERROR, "not Generated");
		assert(0);
		return;
	}

	glBindBuffer(GL_UNIFORM_BUFFER, m_Id);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(ModelData), &m_ModelData, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	Logger::GLError();

	UniformBuffer::Bind();
}

}
}