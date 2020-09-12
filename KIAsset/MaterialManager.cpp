// todo : ˆÚ“®
namespace KI
{
namespace Asset
{

ShadingManager* ShadingManager::m_Instance = NULL;

ShadingManager* ShadingManager::Instance()
{
	if (m_Instance == NULL)
	{
		m_Instance = new ShadingManager();
		m_Instance->Initialize();
	}
	return m_Instance;
}

ShadingManager::ShadingManager()
{
}

ShadingManager::~ShadingManager()
{
}

void ShadingManager::Initialize()
{
	CreateSystemShading();
}

void ShadingManager::CreateSystemShading()
{
	auto pBasicShading = make_shared<BasicShading>(vec4(1, 0, 1, 1));

	m_pShadings[SYSTEM_SHADING_SELECTION] = pBasicShading;

}

shared_ptr<IShading> ShadingManager::GetSystemShading(SYSTEM_SHADING  type)
{
	auto itr = m_pShadings.find(type);
	if (itr == m_pShadings.end())
	{
		assert(0);
		return nullptr;
	}

	return m_pShadings[type];
}
}
}

