namespace KI
{
namespace ShaderLib
{
UniformScene::UniformScene()
	: UniformBuffer(SCENE_DATA_LOCATION)
{
}

UniformScene::~UniformScene()
{
}

void UniformScene::SetViewMatrix(const mat4x4& viewMatrix)
{
	m_data.viewMatrix = viewMatrix;
}
void UniformScene::SetProjection(const mat4x4& projMatrix)
{
	m_data.projection = projMatrix;
}

void UniformScene::Bind()
{
	if (m_Id == 0)
	{
		Logger::Output(LOG_LEVEL::ERROR, "not Generated");
		assert(0);
		return;
	}

	glBindBuffer(GL_UNIFORM_BUFFER, m_Id);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(SceneData), &m_data, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	Logger::GLError();

	UniformBuffer::Bind();
}

}
}