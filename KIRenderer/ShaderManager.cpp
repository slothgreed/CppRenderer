namespace KI
{
namespace Renderer
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

void ShaderManager::Free()
{
	RELEASE_INSTANCE(m_Instance);
}
ShaderManager::ShaderManager()
{
	m_pShaderList.clear();
}

ShaderManager::~ShaderManager()
{
}

shared_ptr<IShader> ShaderManager::Generate(shared_ptr<IShaderBuildInfo> pBuildInfo)
{
	auto pShaderChunk = pBuildInfo->GetShaderChunk();

	auto pShader =  make_shared<IShader>();
	pShader->Build(pBuildInfo);

	m_pShaderList.push_back(pShader);

	return pShader;
}

shared_ptr<IShader> ShaderManager::FindOrNew(shared_ptr<IShaderBuildInfo> pBuildInfo)
{
	for (int i = 0; i < m_pShaderList.size(); i++)
	{
		if (m_pShaderList[i]->Compare(pBuildInfo.get()))
		{
			return m_pShaderList[i];
		}
	}

	return Generate(pBuildInfo);
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
}