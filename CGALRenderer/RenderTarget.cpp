namespace KI
{
RenderTarget::RenderTarget()
{
}

RenderTarget::~RenderTarget()
{
}


void RenderTarget::Resize(int width, int height)
{
	for (int i = 0; i < m_pOutputBuffer.size(); i++)
	{
		m_pOutputBuffer[i]->Resize(width, height);
	}

	m_pDepthBuffer->Resize(width, height);
}

}