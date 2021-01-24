namespace KI
{
namespace Topology
{
CubeArgs::CubeArgs(vec3 min, vec3 max, PrimitiveType type)
	:m_min(min), m_max(max), m_primType(type)
{
}
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

void Cube::Build(const CubeArgs& args)
{
	m_position.resize(8);
	m_position[0] = (args.m_min);
	m_position[1] = (vec3(args.m_max.x, args.m_min.y, args.m_min.z));
	m_position[2] = (vec3(args.m_max.x, args.m_max.y, args.m_min.z));
	m_position[3] = (vec3(args.m_min.x, args.m_max.y, args.m_min.z));

	m_position[4] = (vec3(args.m_min.x, args.m_min.y, args.m_max.z));
	m_position[5] = (vec3(args.m_max.x, args.m_min.y, args.m_max.z));
	m_position[6] = (args.m_max);
	m_position[7] = (vec3(args.m_min.x, args.m_max.y, args.m_max.z));

	if (args.m_primType == CubeArgs::PrimitiveType::TRIANGLES) {
		m_index.resize(36);
		AddTrianlgeIndexFromRectangle(0, 0 + IndexOffset(), 3 + IndexOffset(), 2 + IndexOffset(), 1 + IndexOffset());
		AddTrianlgeIndexFromRectangle(1, 0 + IndexOffset(), 4 + IndexOffset(), 7 + IndexOffset(), 3 + IndexOffset());
		AddTrianlgeIndexFromRectangle(2, 4 + IndexOffset(), 5 + IndexOffset(), 6 + IndexOffset(), 7 + IndexOffset());
		AddTrianlgeIndexFromRectangle(3, 1 + IndexOffset(), 2 + IndexOffset(), 6 + IndexOffset(), 5 + IndexOffset());
		AddTrianlgeIndexFromRectangle(4, 2 + IndexOffset(), 3 + IndexOffset(), 7 + IndexOffset(), 6 + IndexOffset());
		AddTrianlgeIndexFromRectangle(5, 1 + IndexOffset(), 5 + IndexOffset(), 4 + IndexOffset(), 0 + IndexOffset());
		m_drawType = GL_TRIANGLES;
	}
	else
	{
		m_index.resize(24);
		int index = 0;
		// front
		m_index[index++] = 0; m_index[index++] = 1;
		m_index[index++] = 1; m_index[index++] = 2;
		m_index[index++] = 2; m_index[index++] = 3;
		m_index[index++] = 3; m_index[index++] = 0;

		// back
		m_index[index++] = 4; m_index[index++] = 5;
		m_index[index++] = 5; m_index[index++] = 6;
		m_index[index++] = 6; m_index[index++] = 7;
		m_index[index++] = 7; m_index[index++] = 4;

		// depth
		m_index[index++] = 0; m_index[index++] = 4;
		m_index[index++] = 1; m_index[index++] = 5;
		m_index[index++] = 2; m_index[index++] = 6;
		m_index[index++] = 3; m_index[index++] = 7;


		m_drawType = GL_LINES;
	}
	
}

void Cube::AddTrianlgeIndexFromRectangle(int index, int vertex0, int vertex1, int vertex2, int vertex3)
{
	index *= 6;
	m_index[index + 0] = vertex0; m_index[index + 1] = vertex1; m_index[index + 2] = vertex2;
	m_index[index + 3] = vertex0; m_index[index + 4] = vertex2; m_index[index + 5] = vertex3;
}
}
}