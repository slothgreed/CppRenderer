namespace KI
{
namespace Renderer
{

PickManager::PickManager()
{
}

PickManager::~PickManager()
{
	m_pPickObjects.clear();
}

void PickManager::AddPickObject(shared_ptr<IPickable> pPickObject)
{
	m_pPickObjects.push_back(pPickObject);
}

void PickManager::SetPickID()
{
	int startIndex = 0;
	int endIndex = 0;
	for (int i = 0; i < m_pPickObjects.size(); i++)
	{
		m_pPickObjects[i]->SetPickID(startIndex, endIndex);
		startIndex = endIndex;
		endIndex = 0;
	}
}

void PickManager::Dispose()
{
	m_pPickObjects.clear();
}
}
}