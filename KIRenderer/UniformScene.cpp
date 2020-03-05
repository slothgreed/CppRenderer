namespace KI
{
namespace Renderer
{
UniformScene::UniformScene()
{
	m_Id = 0;
}

UniformScene::~UniformScene()
{
}


void UniformScene::Generate()
{
	glGenBuffers(1, &m_Id);
}

void UniformScene::Set(const SceneData& data)
{
	if (m_Id == 0)
	{
		Logger::Output(LOG_LEVEL::ERROR, "not Generated");
		assert(0);
		return;
	}

	glBindBuffer(GL_UNIFORM_BUFFER, m_Id);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(SceneData), &data, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	Logger::GLError();
}

void UniformScene::Bind()
{
	if (m_Id == 0)
	{
		Logger::Output(LOG_LEVEL::ERROR, "not Generated");
		assert(0);
		return;
	}

	glBindBufferBase(GL_UNIFORM_BUFFER, SCENE_DATA_LOCATION, m_Id);
	Logger::GLError();
}

void UniformScene::UnBind()
{
	glBindBufferBase(GL_UNIFORM_BUFFER, SCENE_DATA_LOCATION, 0);
	Logger::GLError();
}

void UniformScene::Dispose()
{
	if (m_Id != 0)
	{
		glDeleteBuffers(1, &m_Id);
		m_Id = 0;
	}
}
}
}