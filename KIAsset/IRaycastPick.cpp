namespace KI
{
namespace Asset
{

RaycastPickInfo::RaycastPickInfo(PICK_TYPE type, Topology::Ray* ray) 
{ 
    m_minDistance = numeric_limits<float>::infinity();
    m_Type = type;
    m_ray = ray;
};

void RaycastPickInfo::SetResult(PICK_TYPE type, const string& id, int first, int count, vec3 position, float distance)
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
    m_position = position;
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