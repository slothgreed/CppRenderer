namespace KI
{
namespace Topology
{
IPrimitive::IPrimitive(int indexOffset)
{
	m_indexOffset = indexOffset;
	m_drawType = GL_NONE;
}

void IPrimitive::Multi(const mat4x4& matrix)
{
	for (int i = 0; i < m_position.size(); i++)
	{
		vec4 position = vec4(m_position[i], 1.0);
		m_position[i] = matrix * position;
	}
}

GLuint IPrimitive::GetDrawType()
{
	if (m_drawType == GL_NONE)
	{
		assert(0);
		return GL_POINTS;
	}
	return m_drawType;
}
}
}