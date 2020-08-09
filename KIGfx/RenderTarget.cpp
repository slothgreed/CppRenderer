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
	for (auto itr = m_pOutputBuffer.begin(); itr != m_pOutputBuffer.end(); itr++)
	{
		if (itr->second != nullptr) {
			itr->second->Resize(width, height);
		}
	}

	if (m_pDepthBuffer != nullptr)
	{
		m_pDepthBuffer->Resize(width, height);
	}

	SetSize(width, height);
}


void RenderTarget::SetRenderTexture(FRAMEBUFFER_ATTACHMENT attachment, const TextureData& textureData)
{
	auto pRenderTexture = make_shared<RenderTexture>();
	pRenderTexture->Generate();
	pRenderTexture->Begin();
	pRenderTexture->Set(textureData);
	pRenderTexture->End();

	if( attachment == FRAMEBUFFER_ATTACHMENT::FRAMEBUFFER_COLOR_ATTACHMENT0 ||
		attachment == FRAMEBUFFER_ATTACHMENT::FRAMEBUFFER_COLOR_ATTACHMENT1 || 
		attachment == FRAMEBUFFER_ATTACHMENT::FRAMEBUFFER_COLOR_ATTACHMENT2 || 
		attachment == FRAMEBUFFER_ATTACHMENT::FRAMEBUFFER_COLOR_ATTACHMENT3)
	{
		pRenderTexture->SetAttachment(GL_COLOR_ATTACHMENT0 + attachment);
		m_pOutputBuffer[attachment] = pRenderTexture;
	}
	else if (attachment == FRAMEBUFFER_ATTACHMENT::FRAMEBUFFER_DEPTH_ATTATCHMENT)
	{
		pRenderTexture->SetAttachment(GL_DEPTH_ATTACHMENT);
		m_pDepthBuffer = pRenderTexture;
	}
	else
	{
		assert(0);
	}

	glFramebufferTexture2D(GL_FRAMEBUFFER, pRenderTexture->Attachment(), GL_TEXTURE_2D, pRenderTexture->ID(), 0);
	Logger::GLError();
}

void RenderTarget::Initialize(map<FRAMEBUFFER_ATTACHMENT, shared_ptr<TextureData>>& pRenderTexture)
{
	m_pFrameBuffer = make_shared<FrameBuffer>();
	m_pFrameBuffer->Generate();
	m_pFrameBuffer->Begin();

	for (auto itr = pRenderTexture.begin(); itr != pRenderTexture.end(); itr++)
	{
		if (itr->second != nullptr) {
			SetRenderTexture(itr->first, *itr->second.get());
		}
	}

	m_pFrameBuffer->Validate();
	m_pFrameBuffer->UnBind();

	Logger::GLError();
}


void RenderTarget::Initialize(int outputBufferNum, int width, int height)
{
	if (outputBufferNum > 4) {
		assert(0);
		outputBufferNum = 4;
	}

	map<FRAMEBUFFER_ATTACHMENT, shared_ptr<TextureData>> renderTextures;

	for (int i = 0; i < outputBufferNum; i++)
	{
		auto data = make_shared<TextureData>(RenderTexture::DefaultColorTextureData(width, height));
	}

	auto data = make_shared<TextureData>(RenderTexture::DefaultDepthTextureData(width, height));
	renderTextures[FRAMEBUFFER_ATTACHMENT::FRAMEBUFFER_DEPTH_ATTATCHMENT] = data;

	Initialize(renderTextures);
}

void RenderTarget::Bind()
{
	m_pFrameBuffer->Bind();

	vector<GLenum> attachment;
	for (auto itr = m_pOutputBuffer.begin(); itr != m_pOutputBuffer.end(); itr++)
	{
		attachment.push_back(itr->second->Attachment());
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
	for (auto itr = m_pOutputBuffer.begin(); itr != m_pOutputBuffer.end(); itr++)
	{
		if (itr->second != nullptr) {
			itr->second->Dispose();
		}
	}

	m_pDepthBuffer->Dispose();
}

shared_ptr<RenderTexture> RenderTarget::ColorTexture(FRAMEBUFFER_ATTACHMENT index)
{
	if (index < 0 || m_pOutputBuffer.size() <= index) {
		assert(0);
		return nullptr;
	}

	return m_pOutputBuffer[index];
}

void RenderTarget::CopyColorBuffer(FRAMEBUFFER_ATTACHMENT index, Texture* texture)
{
	if (m_pOutputBuffer.size() <= index)
	{
		assert(0);
	}

	m_pFrameBuffer->Begin();
	glReadBuffer(m_pOutputBuffer[index]->Attachment());
	glActiveTexture(GL_TEXTURE0);

	TextureData data;
	data.width = m_pOutputBuffer[index]->Width();
	data.height = m_pOutputBuffer[index]->Height();
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
	data.width = m_pDepthBuffer->Width();
	data.height = m_pDepthBuffer->Height();
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

bool RenderTarget::GetPixels(ReadPixelArgs& args, RENDER_TEXTURE_TYPE type, FRAMEBUFFER_ATTACHMENT index)
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