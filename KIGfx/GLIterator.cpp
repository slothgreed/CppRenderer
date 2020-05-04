namespace KI
{
namespace Gfx
{

GL_TRIANGLES_Iterator::GL_TRIANGLES_Iterator(GLuint sourceType, vec3* position, int size)
{
	m_position = position;
	m_index = 0;
	m_size = size;
}

bool GL_TRIANGLES_Iterator::HasNext()
{
	if (sourceType == GL_TRIANGLE_STRIP)
	{
		if (m_index + 2 == m_size)
		{
			return false;
		}
	}
	else if (sourceType == GL_TRIANGLES)
	{
		if (3 * m_index + 2 == m_size)
		{
			return false;
		}
	}
	
	return true;
}

void GL_TRIANGLES_Iterator::Current(vec3& pos0, vec3& pos1, vec3& pos2)
{
	if (sourceType == GL_TRIANGLE_STRIP)
	{
		pos0 = m_position[m_index];
		pos1 = m_position[m_index + 1];
		pos2 = m_position[m_index + 2];
	}
	else if (sourceType == GL_TRIANGLES)
	{
		pos0 = m_position[3 * m_index];
		pos0 = m_position[3 * m_index + 1];
		pos0 = m_position[3 * m_index + 2];
	}
}

void GL_TRIANGLES_Iterator::Next()
{
	m_index++;
}
}
}