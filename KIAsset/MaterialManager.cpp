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
	CreateSystemMaterial();
}

void MaterialManager::CreateSystemMaterial()
{
	auto pBasicMaterial = make_shared<BasicMaterial>(vec4(1, 0, 0, 1));;

	m_pMaterials[SYSTEM_MATERIAL_SELECTION] = pBasicMaterial;

}

shared_ptr<IMaterial> MaterialManager::GetSystemMaterial(SYSTEM_MATERIAL  type)
{
	auto itr = m_pMaterials.find(type);
	if (itr == m_pMaterials.end())
	{
		assert(0);
		return nullptr;
	}

	return m_pMaterials[type];
}
}
}

