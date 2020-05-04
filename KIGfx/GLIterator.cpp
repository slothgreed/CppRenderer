namespace KI
{
namespace Gfx
{

GL_TRIANGLES_Iterator::GL_TRIANGLES_Iterator(GLuint sourceType, vec3* position, int* indexs, int size)
{
	m_sourceType = sourceType;
	m_position = position;
	m_indexList = indexs;
	m_index = 0;
	m_size = size;
}

bool GL_TRIANGLES_Iterator::HasNext()
{
	if (m_sourceType == GL_TRIANGLE_STRIP)
	{
		assert(0);
		if (m_index + 2 == m_size)
		{
			return false;
		}
	}
	else if (m_sourceType == GL_TRIANGLES)
	{
		if (3 * m_index == m_size)
		{
			return false;
		}
	}
	
	return true;
}

void GL_TRIANGLES_Iterator::Current(vec3& pos0, vec3& pos1, vec3& pos2)
{
	if (m_sourceType == GL_TRIANGLE_STRIP)
	{
		if (m_indexList == nullptr)
		{
			pos0 = m_position[m_index];
			pos1 = m_position[m_index + 1];
			pos2 = m_position[m_index + 2];
		}
		else
		{
			pos0 = m_position[m_indexList[m_index]];
			pos1 = m_position[m_indexList[m_index + 1]];
			pos2 = m_position[m_indexList[m_index + 2]];
		}
	}
	else if (m_sourceType == GL_TRIANGLES)
	{
		if (m_indexList == nullptr)
		{
			pos0 = m_position[3 * m_index];
			pos1 = m_position[3 * m_index + 1];
			pos2 = m_position[3 * m_index + 2];
		}
		else
		{
			pos0 = m_position[m_indexList[3 * m_index]];
			pos1 = m_position[m_indexList[3 * m_index + 1]];
			pos2 = m_position[m_indexList[3 * m_index + 2]];
		}
	}
}

void GL_TRIANGLES_Iterator::Next()
{
	m_index++;
}
}
}