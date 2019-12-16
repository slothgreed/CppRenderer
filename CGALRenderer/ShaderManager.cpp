namespace KI
{

ShaderManager* ShaderManager::m_Instance = NULL;

ShaderManager* ShaderManager::Instance()
{
	if (m_Instance == NULL)
	{
		m_Instance = new ShaderManager();
	}
	return m_Instance;
}

ShaderManager::ShaderManager()
{
	m_pShaderList.clear();
}

ShaderManager::~ShaderManager()
{
	if (m_pShaderList.size() != 0)
	{
		assert(0);
	}
}

shared_ptr<IShader> ShaderManager::Generate(const ShaderBuildInfo& buildInfo)
{
	shared_ptr<IShader> shader;
	switch (buildInfo.shaderType)
	{
	case SHADER_TYPE_DEFAULT:
		shader = make_shared<DefaultShader>();
		shader->Build(buildInfo);
		break;
	default:
		assert(0);
		break;
	}

	m_pShaderList.push_back(shader);

	return shader;
}

shared_ptr<IShader> ShaderManager::FindOrNew(const ShaderBuildInfo& buildInfo)
{
	for (int i = 0; i < m_pShaderList.size(); i++)
	{
		if (m_pShaderList[i]->Compare(buildInfo))
		{
			return m_pShaderList[i];
		}
	}

	return Generate(buildInfo);
}

void ShaderManager::Dispose()
{
	for (int i = 0; i < m_pShaderList.size(); i++)
	{
		m_pShaderList[i]->Dispose();
	}

	m_pShaderList.clear();

	RELEASE_INSTANCE(m_Instance);
}

}