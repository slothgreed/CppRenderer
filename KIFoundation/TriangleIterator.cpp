namespace KI
{
namespace Foundation
{
TriangleIterator::TriangleIterator(unsigned int sourceType, const vec3* position, const int* indexs, int32_t size)
{
	if (sourceType == GL_TRIANGLES) {
		m_sourceType = TriangleType::TRIANGLES;
	}
	else {
		m_sourceType = TriangleType::TRIANGLE_STRIP;
	}
	m_position = position;
	m_indexList = indexs;
	m_index = 0;
	m_size = size;
}

TriangleIterator::TriangleIterator(TriangleType sourceType, const vec3* position, const int* indexs, int32_t size)
{
	m_sourceType = sourceType;
	m_position = position;
	m_indexList = indexs;
	m_index = 0;
	m_size = size;
}

int32_t TriangleIterator::TriangleSize()
{
	if (m_sourceType == TRIANGLE_STRIP) {
		return m_size - 2;
	} else if (m_sourceType == TRIANGLES) {
		return m_size / 3;
	} else {
		return 0;
		assert(0);
	}
}

bool TriangleIterator::HasNext()
{
	if (m_sourceType == TRIANGLE_STRIP)
	{
		assert(0);
		if (m_index + 2 == m_size)
		{
			return false;
		}
	}
	else if (m_sourceType == TRIANGLES)
	{
		if (3 * m_index == m_size)
		{
			return false;
		}
	}
	
	return true;
}

void TriangleIterator::Current(vec3* pos0, vec3* pos1, vec3* pos2)
{
	if (m_sourceType == TRIANGLE_STRIP)
	{
		if (m_indexList == nullptr)
		{
			*pos0 = m_position[m_index];
			*pos1 = m_position[m_index + 1];
			*pos2 = m_position[m_index + 2];
		}
		else
		{
			*pos0 = m_position[m_indexList[m_index]];
			*pos1 = m_position[m_indexList[m_index + 1]];
			*pos2 = m_position[m_indexList[m_index + 2]];
		}
	}
	else if (m_sourceType == TRIANGLES)
	{
		if (m_indexList == nullptr)
		{
			*pos0 = m_position[3 * m_index];
			*pos1 = m_position[3 * m_index + 1];
			*pos2 = m_position[3 * m_index + 2];
		}
		else
		{
			*pos0 = m_position[m_indexList[3 * m_index]];
			*pos1 = m_position[m_indexList[3 * m_index + 1]];
			*pos2 = m_position[m_indexList[3 * m_index + 2]];
		}
	}
}

void TriangleIterator::Next()
{
	m_index++;
}
}
}