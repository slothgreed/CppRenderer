namespace KI
{
namespace Foundation
{
BDB::BDB()
{
	Set(vec3(numeric_limits<float>::infinity()),
		vec3(-numeric_limits<float>::infinity()));
}

BDB::~BDB()
{
}

BDB::BDB(vec3 min, vec3 max)
{
	Set(min, max);
}

void BDB::Apply(vec3 position)
{
	m_min.x = glm::min(m_min.x, position.x);
	m_min.y = glm::min(m_min.y, position.y);
	m_min.z = glm::min(m_min.z, position.z);

	m_max.x = glm::max(m_max.x, position.x);
	m_max.y = glm::max(m_max.y, position.y);
	m_max.z = glm::max(m_max.z, position.z);
	Set(m_min, m_max);
}

void BDB::Set(vec3 min, vec3 max)
{
	m_min = min;
	m_max = max;
	m_center = vec3(
		m_min.x + m_max.x * 0.5,
		m_min.y + m_max.y * 0.5,
		m_min.z + m_max.z * 0.5
	);
}

std::string BDB::ToString()
{
	// min(x, y, z) : max(x, y, z);
	string str;
	str += "min " + MathHelper::ToString(m_min) + ":";
	str += "max " + MathHelper::ToString(m_max) + ";";

	return str;
}
}
}