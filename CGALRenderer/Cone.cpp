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
	m_index.push_back(0);

	float rad = pi<float>() / partition;
	for (int i = 0; i < partition; i++)
	{
		vec3 position;
		MathHelper::SphericalToCartesian(radius, rad, 1, position);
		position *= radius;
		m_position.push_back(position);
		m_index.push_back(i + 1);
	}

	// I’[‚ðŒ‹‚Ô
	m_index.push_back(1);
}
}