namespace KI
{
namespace Renderer
{

PickPath::PickPath()
{
}

PickPath::~PickPath()
{

}

void PickPath::Initialize(int width, int height)
{
	auto pBuildInfo = make_shared<IShaderBuildInfo>();
	pBuildInfo->SetShaderChunk(make_shared<PickShading>());
	m_pPickShader = ShaderManager::Instance()->FindOrNew(pBuildInfo);
	m_pRenderTarget = make_shared<RenderTarget>();
	m_pRenderTarget->SetClearColor(vec4(0));
	map<FRAMEBUFFER_ATTACHMENT, shared_ptr<TextureData>> renderTexture;

	auto textureData = make_shared<TextureData>();
	textureData->target = GL_TEXTURE_2D;
	textureData->level = 0;
	textureData->internalformat = GL_RGB32F;
	textureData->width = width;
	textureData->height = height;
	textureData->border = 0;
	textureData->format = GL_RGB;
	textureData->type = GL_FLOAT;
	textureData->pixels = 0;
	renderTexture[FRAMEBUFFER_COLOR_ATTACHMENT0] = textureData;

	auto depthData = make_shared<TextureData>(RenderTexture::DefaultDepthTextureData(width, height));
	renderTexture[FRAMEBUFFER_ATTACHMENT::FRAMEBUFFER_DEPTH_ATTATCHMENT] = depthData;
	m_pRenderTarget->Initialize(renderTexture);
}

void PickPath::Resize(int width, int height)
{
	m_pRenderTarget->Resize(width, height);
}

shared_ptr<RenderTexture> PickPath::GetPickTexture()
{
	return m_pRenderTarget->GetColorTexture(FRAMEBUFFER_COLOR_ATTACHMENT0);
}

void PickPath::ResetPickID(shared_ptr<Scene> pScene)
{
	int next = 1;
	for (int i = 0; i < pScene->ModelNodes().size(); i++)
	{
		pScene->ModelNodes()[i]->AddPickID(next, &next);
	}
}

void PickPath::Draw(shared_ptr<Scene> pScene)
{
	m_pRenderTarget->Begin();
	m_pRenderTarget->Clear();
	
	pScene->Bind();
	pScene->PickDraw(m_pPickShader);
	pScene->UnBind();
	
	m_pRenderTarget->End();
}

bool PickPath::GetPickResult(const vec2& position, PickResult* pickResult)
{
	m_pRenderTarget->Begin();

	ReadPixelArgs pixelArgs;
	pixelArgs.x = position.x;
	pixelArgs.y = position.y;
	pixelArgs.width = 1;
	pixelArgs.height = 1;

	GetPickTexture()->GetPixels(pixelArgs);

	vec3 value = pixelArgs.pixels.GetVector3(0);
	pickResult->objectID = value.x;
	pickResult->primitiveID = value.y;
	m_pRenderTarget->End();

	Logger::Output(LOG_LEVEL::LOG_LEVEL_DEBUG, MathHelper::ToString(value) + "\n");
	return true;
}
}
}