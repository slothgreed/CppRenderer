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

	return m_pickId[index];
}
}
}