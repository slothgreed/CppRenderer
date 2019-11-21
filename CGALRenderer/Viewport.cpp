namespace KI
{
Viewport::Viewport()
{
	m_position = ivec2();
	m_size = ivec2(100, 100);
}

Viewport::~Viewport()
{
}

void Viewport::SetPosition(int x, int y)
{
	m_position.x = x;
	m_position.y = y;
	glViewport(m_position.x, m_position.y, m_size.x, m_size.y);
}

void Viewport::Resize(int width, int height)
{
	m_size.x = width;
	m_size.y = height;
	glViewport(m_position.x, m_position.y, m_size.x, m_size.y);
}

void Viewport::ConvertWindowToScreenCoordinate(const vec2& position, vec2& result)
{
	float width = 1.0f / m_size.x;
	float height = 1.0f / m_size.y;

	result.x = 2 * position.x * width - 1.0f;
	result.y = 2 * position.y * height - 1.0f;
	result.y *= -1;
}
}