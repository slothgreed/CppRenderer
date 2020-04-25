namespace KI
{
namespace Renderer
{

void RaycastPickInfo::SetResult(PICK_TYPE type, const string& id, void* obj, float distance)
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
    m_object = obj; 
};

bool RaycastPickInfo::Success()
{
    if (m_object != NULL)
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