namespace KI
{
namespace Asset
{	
SSLICEffect::SSLICEffect()
{
}

SSLICEffect::~SSLICEffect()
{
}

void SSLICEffect::Initialize(int width, int height)
{
	TextureData textureData;
	if (width != height)
	{
		assert(0);
		width = height;
	}

	TextureGenerator::RandomTexture(width,15, textureData);
	m_pNoizeTexture = make_shared<Texture>();
	m_pNoizeTexture->Generate();
	m_pNoizeTexture->Begin();
	m_pNoizeTexture->Set(textureData);
	m_pNoizeTexture->End();

	m_pRenderTarget = make_shared<RenderTarget>();
	m_pRenderTarget->Initialize(1, 256, 256);

	m_pPlaneData = make_shared<RenderData>();
	ModelGenerator::Plane(m_pPlaneData.get(), VERTEX_LAYOUT_TEXCOORD);

	TextureData blendTexture;
	blendTexture.width = 256;
	blendTexture.height = 256;
	m_pBlendTexture = make_shared<Texture>();
	m_pBlendTexture->Generate();
	m_pBlendTexture->Begin();
	m_pBlendTexture->Set(blendTexture);
	m_pBlendTexture->End();

	m_pBasicShading = make_shared<BasicShading>(m_pBlendTexture);

	auto pBuildInfo = make_shared<IShaderBuildInfo>();
	pBuildInfo->SetShaderChunk(m_pBasicShading);
	m_pBasicShader = ShaderManager::Instance()->FindOrNew(pBuildInfo);

	auto pSSLICShading = make_shared<BasicShading>(vec4(1,0,0,1));

	m_pPlaneData->SetShading(pSSLICShading);
}

shared_ptr<Texture> SSLICEffect::RenderTexture(int index)
{
	if (index == 0)
	{
		return m_pRenderTarget->ColorTexture(FRAMEBUFFER_COLOR_ATTACHMENT0);
	}

	if (index == 1)
	{
		return m_pNoizeTexture;
	}

	if (index == 2)
	{
		return m_pBlendTexture;
	}

	return nullptr;
}
void SSLICEffect::SetModelNode(shared_ptr<IModelNode> pModelNode)
{
	m_pModelNode = pModelNode;
}

void SSLICEffect::Draw(shared_ptr<UniformStruct> pUniform)
{
	m_pRenderTarget->Begin();
	m_pRenderTarget->Clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_pModelNode->FixedShaderDraw(m_pBasicShader, m_pBasicShading, pUniform);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC1_ALPHA);
	m_pPlaneData->Draw(pUniform);
	glDisable(GL_BLEND);

	m_pRenderTarget->CopyColorBuffer(FRAMEBUFFER_COLOR_ATTACHMENT0, m_pBlendTexture.get());
	m_pRenderTarget->End();
}

void SSLICEffect::Resize(int width, int height)
{

}

}
}