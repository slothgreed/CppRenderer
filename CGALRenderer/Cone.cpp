namespace KI
{
Cone::Cone()
{
}

Cone::~Cone()
{
}

void Cone::Build(float radius, float height, int partition)
{
	m_position.push_back(vec3(0, height, 0));
	m_position.push_back(vec3(0, 0, 0));

	float rad = 2 * pi<float>() / partition;
	float theta = 0;

	for (int i = 0; i <= partition; i++)
	{
		vec3 position;
		MathHelper::SphericalToCartesian(radius, -(i * rad), pi<float>()/2, position);
		m_position.push_back(position);
		Logger::Output(LOG_LEVEL::DEBUG, (MathHelper::ToString(position)+"\n").data() );
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

		m_index.push_back(0);			// 先端点
		m_index.push_back(index1);
		m_index.push_back(index2);

		// 終端を結ぶ
		m_index.push_back(1);			// 底面の中心点
		m_index.push_back(index2);
		m_index.push_back(index1);
	}

}
}