namespace KI
{
namespace RenderView
{

ViewViewModel::ViewViewModel()
{
}

ViewViewModel::~ViewViewModel()
{
}

void ViewViewModel::SetController(CONTROLER_TYPE type, IController* value)
{
	m_pController[type] = value; 
	m_CurrentController = type;

}

void ViewViewModel::Dispose()
{
	for (auto itr = m_pController.begin(); itr != m_pController.end(); itr++)
	{
		delete itr->second;
	}

	ShaderManager::Free();
}


}
}