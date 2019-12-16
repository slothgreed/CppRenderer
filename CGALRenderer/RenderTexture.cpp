namespace KI
{
RenderTexture::RenderTexture()
{
}

RenderTexture::~RenderTexture()
{
}


void RenderTexture::Resize(int width, int height)
{
	m_data.width = width;
	m_data.height = height;
	m_data.pixels = 0;
	Set(m_data);
}
}

