namespace KI
{
	
SSLICEffect::SSLICEffect()
{
}

SSLICEffect::~SSLICEffect()
{
}

void SSLICEffect::Initialize()
{
	int size = 64;
	TextureData textureData;
	TextureGenerator::RandomTexture(size,15, textureData);
	m_pNoizeTexture = make_shared<Texture>();
	m_pNoizeTexture->Generate();
	m_pNoizeTexture->Set(textureData);

	m_pRenderTarget = make_shared<RenderTarget>();
	m_pRenderTarget->Initialize(1, 256, 256);

	m_pPlaneBuffer = make_shared<DefaultVertexBuffer>();
	ModelGenerator::RenderPlane(m_pPlaneBuffer.get());

	ShaderBuildInfo buildInfo;
	DefaultShader::GetVertexShaderDefine(VERTEX_LAYOUT::VERTEX_LAYOUT_PT, buildInfo);
	DefaultShader::GetFragShaderDefine(VERTEX_LAYOUT::VERTEX_LAYOUT_PT, buildInfo);
	m_pModelShader = static_pointer_cast<DefaultShader>(ShaderManager::Instance()->FindOrNew(buildInfo));

}

void SSLICEffect::Draw()
{

	m_pRenderTarget->ColorTexture(0)->Begin();
	m_pModelShader->BindColorTexture();

	m_pModel->Draw();
	
	m_pRenderTarget->ColorTexture(0)->End();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC1_ALPHA);
	m_pNoizeTexture->Begin();
	m_pSSLICShader->BindColorTexture();
	m_pPlaneBuffer->Draw();
	m_pNoizeTexture->End();
	glDisable(GL_BLEND);
}

void SSLICEffect::Resize(int width, int height)
{

}

}