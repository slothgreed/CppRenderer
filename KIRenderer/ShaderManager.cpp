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

shared_ptr<IShader> ShaderManager::Generate(shared_ptr<IShaderBuildInfo> buildInfo)
{
	shared_ptr<IShader> pShader;
	switch (buildInfo->Type())
	{
	case SHADER_TYPE_DEFAULT:
		pShader = make_shared<DefaultShader>();
		pShader->Build(buildInfo);
		break;
	case SHADER_TYPE_OUTPUT:
		pShader = make_shared<OutputShader>();
		pShader->Build(buildInfo);
		break;
	case SHADER_TYPE_SSLIC:
		pShader = make_shared<SSLICShader>();
		pShader->Build(buildInfo);
		break;
	case SHADER_TYPE_GRAYSCALE:
		pShader = make_shared<GrayScaleShader>();
		pShader->Build(buildInfo);
		break;
	case SHADER_TYPE_COMPOSIT:
		pShader = make_shared<CompositShader>();
		pShader->Build(buildInfo);
	case SHADER_TYPE_NORMALVISUALIZE:
		pShader = make_shared<NormalVisualizeShader>();
		pShader->Build(buildInfo);
		break;
	case SHADER_TYPE_BEZIERLINE:
		pShader = make_shared<BezierLineShader>();
		pShader->Build(buildInfo);
		break;
	default:
		assert(0);
		break;
	}

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