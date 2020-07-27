namespace KI
{
namespace Gfx
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

	SetSize(width, height);
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
		m_pOutputBuffer[i]->Begin();
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
		m_pOutputBuffer[i]->End();
	}

	m_pDepthBuffer = make_shared<RenderTexture>();
	m_pDepthBuffer->Generate();
	m_pDepthBuffer->Begin();
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
	m_pDepthBuffer->End();

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

	glDrawBuffers((GLsizei)m_pOutputBuffer.size(), attachment.data());

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
	if (index < 0 || m_pOutputBuffer.size() <= index) {
		assert(0);
		return nullptr;
	}

	return m_pOutputBuffer[index];
}

void RenderTarget::CopyColorBuffer(int index, Texture* texture)
{
	if (m_pOutputBuffer.size() <= index)
	{
		assert(0);
	}

	m_pFrameBuffer->Begin();
	glReadBuffer(m_pOutputBuffer[index]->Attachment());
	glActiveTexture(GL_TEXTURE0);

	TextureData data;
	data.width = m_pOutputBuffer[0]->Width();
	data.height = m_pOutputBuffer[0]->Height();
	texture->Begin();
	//texture->Set(data);
	glCopyTexSubImage2D(
		data.target,
		data.level,
		0, 0, 0, 0,
		data.width,
		data.height);
	texture->End();
	m_pFrameBuffer->End();
}

void RenderTarget::CopyDepthBuffer(Texture* texture)
{
	m_pFrameBuffer->Begin();
	glReadBuffer(GL_DEPTH_COMPONENT);
	glActiveTexture(GL_TEXTURE0);

	TextureData data;
	data.width = m_pOutputBuffer[0]->Width();
	data.height = m_pOutputBuffer[0]->Height();
	texture->Begin();
	texture->Set(data);
	glCopyTexSubImage2D(
		data.target,
		data.level,
		0, 0, 0, 0,
		data.width,
		data.height);
	texture->End();
	m_pFrameBuffer->End();
}

bool RenderTarget::GetPixels(ReadPixelArgs& args, RENDER_TEXTURE_TYPE type, int index)
{
	RenderTexture* pRenderTexture = nullptr;
	if (type == RENDER_TEXTURE_TYPE::RENDER_COLOR_TEXTURE) {
		pRenderTexture = ColorTexture(index).get();
	}
	else if(type == RENDER_TEXTURE_TYPE::RENDER_DEPTH_TEXTURE)
	{
		pRenderTexture = m_pDepthBuffer.get();
	}
	else
	{
		assert(0);
		return false;
	}

	args.format = pRenderTexture->Format();
	args.type = pRenderTexture->ColorComponentType();

	return IRenderTarget::GetPixels(args);
}
}
};