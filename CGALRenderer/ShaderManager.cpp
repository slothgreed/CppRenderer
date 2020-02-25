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

shared_ptr<IShader> ShaderManager::Generate(shared_ptr<IShaderDefine> shaderDefine)
{
	shared_ptr<IShader> shader;
	switch (shaderDefine->Type())
	{
	case SHADER_TYPE_DEFAULT:
		shader = make_shared<DefaultShader>();
		shader->Build(shaderDefine);
		break;
	case SHADER_TYPE_OUTPUT:
		shader = make_shared<OutputShader>();
		shader->Build(shaderDefine);
		break;
	case SHADER_TYPE_SSLIC:
		shader = make_shared<SSLICShader>();
		shader->Build(shaderDefine);
		break;
	case SHADER_TYPE_GRAYSCALE:
		shader = make_shared<GrayScaleShader>();
		shader->Build(shaderDefine);
		break;
	default:
		assert(0);
		break;
	}

	m_pShaderList.push_back(shader);

	return shader;
}

shared_ptr<IShader> ShaderManager::FindOrNew(shared_ptr<IShaderDefine> shaderDefine)
{
	for (int i = 0; i < m_pShaderList.size(); i++)
	{
		if (m_pShaderList[i]->Compare(shaderDefine.get()))
		{
			return m_pShaderList[i];
		}
	}

	return Generate(shaderDefine);
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