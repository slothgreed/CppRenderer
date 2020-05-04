namespace KI
{
namespace Renderer
{

void RaycastPickInfo::SetResult(PICK_TYPE type, const string& id, int first, int count, float distance)
{
    if (m_pickItemType & ~type)
    {
        assert(0);
    }

    if (distance > m_minDistance)
    {
        assert(0);
    }

    m_pickItemType = type;
    m_minDistance = distance; 
    m_identifier = id; 
    m_first = first;
    m_count = count;
};

bool RaycastPickInfo::Success()
{
    if (m_count != 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
}
}