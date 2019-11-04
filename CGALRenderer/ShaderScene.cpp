
ShaderScene::ShaderScene()
{
	m_SceneId = 0;
	m_SceneBlockId = 0;
}

ShaderScene::~ShaderScene()
{
}


void ShaderScene::Generate()
{
	glGenBuffers(1, &m_SceneId);

}

void ShaderScene::Set(const SceneData& data)
{
	if (m_SceneId == 0)
	{
		Logger::Output(LOG_LEVEL::ERROR, "not initialized");
		assert(0);
		return;
	}

	glBindBuffer(GL_UNIFORM_BUFFER, m_SceneId);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(SceneData), &data, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	Logger::GLError();
}

void ShaderScene::BindBlock(GLuint program)
{
	m_SceneBlockId = glGetUniformBlockIndex(program, "Scene");
	glUniformBlockBinding(program, m_SceneBlockId, SCENE_DATA_LOCATION);
	Logger::GLError();
}

void ShaderScene::Use()
{
	if (m_SceneId == 0)
	{
		Logger::Output(LOG_LEVEL::ERROR, "not initialized");
		assert(0);
		return;
	}

	glBindBufferBase(GL_UNIFORM_BUFFER, SCENE_DATA_LOCATION, m_SceneId);
	Logger::GLError();
}