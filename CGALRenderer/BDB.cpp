BDB::BDB()
{
	Set(vec3(0), vec3(0));
}

BDB::~BDB()
{
}

BDB::BDB(vec3 min, vec3 max)
{
	Set(min, max);
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