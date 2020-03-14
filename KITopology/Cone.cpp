namespace KI
{
namespace Topology
{
Cone::Cone()
{
}

Cone::~Cone()
{
}

void Cone::Build(float radius, float height, int partition)
{
	m_position.clear();
	m_index.clear();
	m_position.push_back(vec3(0, height, 0));
	m_position.push_back(vec3(0, 0, 0));

	float rad = 2 * pi<float>() / partition;
	float theta = 0;

	for (int i = 0; i <= partition; i++)
	{
		vec3 position;
		MathHelper::SphericalToCartesian(radius, -(i * rad), pi<float>()/2, position);
		m_position.push_back(position);
	}

	int index1;
	int index2;
	for (int i = 0; i <= partition; i++)
	{

		index1 = 2 + i;
		if (2 + i + 1 == m_position.size())
		{
			index2 = 2;
		}
		else
		{
			index2 = 2 + i + 1;
		}

		m_index.push_back(0		 + IndexOffset());			// 先端点
		m_index.push_back(index1 + IndexOffset());
		m_index.push_back(index2 + IndexOffset());

		// 終端を結ぶ
		m_index.push_back(1		 + IndexOffset());			// 底面の中心点
		m_index.push_back(index2 + IndexOffset());
		m_index.push_back(index1 + IndexOffset());
	}

}
}
}