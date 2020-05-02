namespace KI
{
namespace Topology
{

Icosahedron::Icosahedron()
{
}


Icosahedron::~Icosahedron()
{
}

void Icosahedron::Build(const IcosahedronArgs& args)
{
	m_position.resize(12);

	m_position[0] = vec3(0, args.m_radial, args.m_radial);
	m_position[1] = vec3(0, args.m_radial, -args.m_radial);
	m_position[2] = vec3(0, -args.m_radial, args.m_radial);
	m_position[3] = vec3(0, -args.m_radial, -args.m_radial);

	m_position[4] = vec3(args.m_radial, args.m_radial, 0);
	m_position[5] = vec3(args.m_radial, -args.m_radial, 0);
	m_position[6] = vec3(-args.m_radial, args.m_radial, 0);
	m_position[7] = vec3(-args.m_radial, -args.m_radial, 0);

	m_position[8] =  vec3(args.m_radial, 0, args.m_radial);
	m_position[9] =  vec3(-args.m_radial, 0, args.m_radial);
	m_position[10] = vec3(args.m_radial, 0, -args.m_radial);
	m_position[11] = vec3(-args.m_radial, 0, -args.m_radial);

	m_normal.resize(12);
	for (int i = 0; i < m_position.size(); i++)
	{
		m_normal[i] = glm::normalize(m_position[i]);
	}

	int indexArray[60] = {
		1, 0, 4, 0, 1, 6, 2, 3, 5, 3, 2, 7,
		4, 5, 10, 5, 4, 8, 6, 7, 9, 7, 6, 11,
		8, 9, 2, 9, 8, 0, 10, 11, 1, 11, 10, 3,
		0, 8, 4, 0, 6, 9, 1, 4, 10, 1, 11, 6,
		2, 5, 8, 2, 9, 7, 3, 10, 5, 3, 7, 11 };
	m_index.insert(m_index.begin(), std::begin(indexArray), std::end(indexArray));
}

}
}