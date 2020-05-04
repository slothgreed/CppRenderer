namespace KI
{
namespace Topology
{

Quad::Quad()
{
}

Quad::~Quad()
{
}

void Quad::Build(const QuadArgs& args)
{
	m_position.reserve(4);
	m_position[0] = vec3(args.m_min.x, args.m_min.y, 0);
	m_position[1] = vec3(args.m_max.x, args.m_min.y, 0);
	m_position[2] = vec3(args.m_min.x, args.m_max.y, 0);
	m_position[3] = vec3(args.m_max.x, args.m_max.y, 0);

	m_drawType = GL_TRIANGLE_STRIP;
}
}
}