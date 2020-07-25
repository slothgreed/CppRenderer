namespace KI
{
namespace Topology
{

Torus::Torus(const TorusArgs& args)
{
	Build(args);
}

Torus::~Torus()
{
}
void Torus::Build(const TorusArgs& args)
{
	float sideAngle = pi<float>() * 2 / args.nsides;
	float ringAngle = pi<float>() * 2 / args.rings;
	for (int i = 0; i <= args.nsides; i++)
	{
		float r = sideAngle * i;
		float rr = (float)cos(r);
		float ry = (float)sin(r);

		for (int j = 0; j <= args.rings; j++)
		{
			float tr = ringAngle * j;
			float tx = (rr * args.inRad + args.outRad) * (float)cos(tr);
			float ty = ry * args.inRad;
			float tz = (rr * args.inRad + args.outRad) * (float)sin(tr);
			m_position.push_back(vec3(tx, ty, tz));

			float rx = rr * (float)cos(tr);
			float rz = rr * (float)sin(tr);
			m_normal.push_back(vec3(rx, ry, rz));

			if (i != args.nsides && j != args.rings) {
				r = (args.rings + 1) * i + j;
				m_index.push_back(r);
				m_index.push_back(r + args.rings + 1);
				m_index.push_back(r + 1);

				m_index.push_back(r + args.rings + 1);
				m_index.push_back(r + args.rings + 2);
				m_index.push_back(r + 1);
			}
		}
	}
	
	m_drawType = GL_TRIANGLES;
}
}
}