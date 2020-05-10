// todo : ˆÚ“®
namespace KI
{
namespace Asset
{

MaterialManager* MaterialManager::m_Instance = NULL;

MaterialManager* MaterialManager::Instance()
{
	if (m_Instance == NULL)
	{
		m_Instance = new MaterialManager();
		m_Instance->Initialize();
	}
	return m_Instance;
}

MaterialManager::MaterialManager()
{
}

MaterialManager::~MaterialManager()
{
}

void MaterialManager::Initialize()
{
	CreateSystemShaderPass();
}

void MaterialManager::CreateSystemShaderPass()
{
	auto pShaderPass = make_unique<DefaultShaderPass>(
		make_shared<BasicMaterial>(vec4(1, 0, 0, 1)));

	m_pShaderPasss[SYSTEM_MATERIAL_SELECTION] = std::move(pShaderPass);

}

shared_ptr<IShaderPass> MaterialManager::GetSystemShaderPass(SYSTEM_MATERIAL systemShaderPass)
{
	auto itr = m_pShaderPasss.find(systemShaderPass);
	if (itr == m_pShaderPasss.end())
	{
		assert(0);
		return nullptr;
	}

	return m_pShaderPasss[systemShaderPass];
}
}
}

