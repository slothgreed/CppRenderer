namespace KI
{

void IPrimitive::Multi(const mat4x4& matrix)
{
	vec3 position;
	for (int i = 0; i < m_position.size(); i++)
	{
		vec4 position = vec4(m_position[i], 1.0);
		m_position[i] = matrix * position;
	}
}
}