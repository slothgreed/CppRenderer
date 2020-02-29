namespace KI
{

Cube::Cube(int indexOffset)
	:IPrimitive(indexOffset)
{
}
Cube::Cube()
{
}

Cube::~Cube()
{
}

void Cube::Build(const vec3& min, const vec3& max)
{
	m_position.resize(8);
	m_position[0] = (min);
	m_position[1] = (vec3(max.x, min.y, min.z));
	m_position[2] = (vec3(max.x, max.y, min.z));
	m_position[3] = (vec3(min.x, max.y, min.z));
			  	   
	m_position[4] = (vec3(min.x, min.y, max.z));
	m_position[5] = (vec3(max.x, min.y, max.z));
	m_position[6] = (max);
	m_position[7] = (vec3(min.x, max.y, max.z));

	m_index.resize(36);
	AddTrianlgeIndexFromRectangle(0, 0 + IndexOffset(), 3 + IndexOffset(), 2 + IndexOffset(), 1 + IndexOffset());
	AddTrianlgeIndexFromRectangle(1, 0 + IndexOffset(), 4 + IndexOffset(), 7 + IndexOffset(), 3 + IndexOffset());
	AddTrianlgeIndexFromRectangle(2, 4 + IndexOffset(), 5 + IndexOffset(), 6 + IndexOffset(), 7 + IndexOffset());
	AddTrianlgeIndexFromRectangle(3, 1 + IndexOffset(), 2 + IndexOffset(), 6 + IndexOffset(), 5 + IndexOffset());
	AddTrianlgeIndexFromRectangle(4, 2 + IndexOffset(), 3 + IndexOffset(), 7 + IndexOffset(), 6 + IndexOffset());
	AddTrianlgeIndexFromRectangle(5, 1 + IndexOffset(), 5 + IndexOffset(), 4 + IndexOffset(), 0 + IndexOffset());
}

void Cube::AddTrianlgeIndexFromRectangle(int index, int vertex0, int vertex1, int vertex2, int vertex3)
{
	index *= 6;
	m_index[index + 0] = vertex0; m_index[index + 1] = vertex1; m_index[index + 2] = vertex2;
	m_index[index + 3] = vertex0; m_index[index + 4] = vertex2; m_index[index + 5] = vertex3;
}

}