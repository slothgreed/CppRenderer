namespace KI
{
namespace Asset
{

Grid::Grid(const GridArgs& args)
{
	Build(args);
}

Grid::~Grid()
{
}

void Grid::Build(const GridArgs& args)
{
	ivec2 num;
	num.x = args.m_size.x / args.m_Interval.x;
	num.y = args.m_size.y / args.m_Interval.y;

	for (int i = 0; i <= num.x; i++)
	{
		float intervalPos = i * args.m_Interval.x;
		m_position.push_back(vec3(intervalPos, 0, 0));
		m_position.push_back(vec3(intervalPos, args.m_size.y, 0));
	}

	for (int j = 0; j <= num.y; j++)
	{
		float intervalPos = j * args.m_Interval.y;
		m_position.push_back(vec3(0, intervalPos, 0));
		m_position.push_back(vec3(args.m_size.x, intervalPos, 0));
	}

	m_drawType = GL_LINES;
}


}
}