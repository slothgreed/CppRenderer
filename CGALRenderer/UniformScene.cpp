namespace KI
{

UniformScene::UniformScene()
{
	m_SceneId = 0;
}

UniformScene::~UniformScene()
{
}


void UniformScene::Generate()
{
	glGenBuffers(1, &m_SceneId);
}

void UniformScene::Set(const SceneData& data)
{
	if (m_SceneId == 0)
	{
		Logger::Output(LOG_LEVEL::ERROR, "not Generated");
		assert(0);
		return;
	}

	glBindBuffer(GL_UNIFORM_BUFFER, m_SceneId);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(SceneData), &data, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	Logger::GLError();
}

void UniformScene::Bind()
{
	if (m_SceneId == 0)
	{
		Logger::Output(LOG_LEVEL::ERROR, "not Generated");
		assert(0);
		return;
	}

	glBindBufferBase(GL_UNIFORM_BUFFER, SCENE_DATA_LOCATION, m_SceneId);
	Logger::GLError();
}

void UniformScene::UnBind()
{
	glBindBufferBase(GL_UNIFORM_BUFFER, SCENE_DATA_LOCATION, 0);
	Logger::GLError();
}
}