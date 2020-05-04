namespace KI
{
namespace Topology
{

Quad::Quad(const QuadArgs& args)
{
	Build(args);
}

void Quad::Build(const QuadArgs& args)
{
	m_position.resize(4);
	m_position[0] = vec3(args.m_min.x, args.m_min.y, 0);
	m_position[1] = vec3(args.m_max.x, args.m_min.y, 0);
	m_position[2] = vec3(args.m_min.x, args.m_max.y, 0);
	m_position[3] = vec3(args.m_max.x, args.m_max.y, 0);

	m_index.resize(6);
	m_index[0] = 0;
	m_index[1] = 1;
	m_index[2] = 2;
	m_index[3] = 1;
	m_index[4] = 3;
	m_index[5] = 2;

	m_drawType = GL_TRIANGLES;
}
}
}