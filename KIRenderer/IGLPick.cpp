namespace KI
{
namespace Renderer
{

int IGLPick::GetPickID(int index)
{
	if (m_pickId.size() <= index)
	{
		//assert(0);
		return 0;
	}

	// 1ノード内に複数ジオメトリがある。
	return m_pickId[index];
}

bool IGLPick::HasPickID(int id, int* index)
{
	for (int i = 0; i < m_pickId.size(); i++)
	{
		if (m_pickId[i] == id)
		{
			*index = i;
			return true;
		}
	}

	*index = -1;
	return false;
}
void IGLPick::AddPickID(int start, int* next)
{
	m_pickId.push_back(start); 
	*next = start + 1;
};
}
}