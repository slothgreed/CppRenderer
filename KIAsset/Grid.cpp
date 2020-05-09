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
	ivec3 num;
	num.x = args.m_size.x / args.m_gap.x;
	num.y = args.m_size.y / args.m_gap.y;
	num.z = args.m_size.z / args.m_gap.z;

	for (int i = 0; i < num.x; i++)
	{
		for (int j = 0; j < num.y; j++)
		{
			for (int k = 0; k < num.z; k++)
			{

			}
		}
	}
}

}
}