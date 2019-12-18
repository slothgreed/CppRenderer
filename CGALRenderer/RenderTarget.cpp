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

	if (m_pDepthBuffer != nullptr)
	{
		m_pDepthBuffer->Resize(width, height);
	}
}

void RenderTarget::Initialize(int outputBufferNum, int width, int height)
{
	m_pFrameBuffer = make_shared<FrameBuffer>();
	m_pFrameBuffer->Generate();
	m_pFrameBuffer->Bind();

	for (int i = 0; i < outputBufferNum; i++)
	{
		m_pOutputBuffer.push_back(make_shared<RenderTexture>());
		m_pOutputBuffer[i]->Generate();
		m_pOutputBuffer[i]->SetAttachment(GL_COLOR_ATTACHMENT0 + i);
		TextureData data;
		data.target = GL_TEXTURE_2D;
		data.level = 0;
		data.internalformat = GL_RGBA;
		data.width = width;
		data.height = height;
		data.border = 0;
		data.format = GL_RGBA;
		data.type = GL_UNSIGNED_BYTE;
		data.pixels = 0;
		m_pOutputBuffer[i]->Set(data);
	}

	m_pDepthBuffer = make_shared<RenderTexture>();
	m_pDepthBuffer->Generate();
	m_pDepthBuffer->SetAttachment(GL_DEPTH_ATTACHMENT);
	TextureData data;
	data.target = GL_TEXTURE_2D;
	data.level = 0;
	data.internalformat = GL_DEPTH_COMPONENT;
	data.width = width;
	data.height = height;
	data.border = 0;
	data.format = GL_DEPTH_COMPONENT;
	data.type = GL_UNSIGNED_BYTE;
	data.pixels = 0;
	m_pDepthBuffer->Set(data);

	for (int i = 0; i < m_pOutputBuffer.size(); i++)
	{
		glFramebufferTexture2D(GL_FRAMEBUFFER, m_pOutputBuffer[i]->Attachment(), GL_TEXTURE_2D, m_pOutputBuffer[i]->ID(), 0);
	}
	Logger::GLError();

	glFramebufferTexture2D(GL_FRAMEBUFFER, m_pDepthBuffer->Attachment(), GL_TEXTURE_2D, m_pDepthBuffer->ID(), 0);

	Logger::GLError();


	m_pFrameBuffer->UnBind();
}

void RenderTarget::Bind()
{
	m_pFrameBuffer->Bind();

	vector<GLenum> attachment;
	for (int i = 0; i < m_pOutputBuffer.size(); i++)
	{
		attachment.push_back(m_pOutputBuffer[i]->Attachment());
	}

	glDrawBuffers(m_pOutputBuffer.size(), attachment.data());

	Logger::GLError();

}
void RenderTarget::UnBind()
{
	m_pFrameBuffer->UnBind();

	glDrawBuffer(GL_BACK);
	Logger::GLError();
}

void RenderTarget::Dispose()
{
	m_pFrameBuffer->Dispose();
	for (int i = 0; i < m_pOutputBuffer.size(); i++)
	{
		m_pOutputBuffer[i]->Dispose();
	}

	m_pDepthBuffer->Dispose();
}

shared_ptr<RenderTexture> RenderTarget::ColorTexture(int index)
{
	return m_pOutputBuffer[index];
}
};