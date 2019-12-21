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
	m_pNoizeTexture->Begin();
	m_pNoizeTexture->Set(textureData);
	m_pNoizeTexture->End();

	m_pRenderTarget = make_shared<RenderTarget>();
	m_pRenderTarget->Initialize(1, 256, 256);

	m_pPlaneBuffer = make_shared<DefaultVertexBuffer>();
	ModelGenerator::RenderPlane(m_pPlaneBuffer.get());

	ShaderBuildInfo buildInfo;
	DefaultShader::GetVertexShaderDefine(VERTEX_LAYOUT::VERTEX_LAYOUT_PT, buildInfo);
	DefaultShader::GetFragShaderDefine(VERTEX_LAYOUT::VERTEX_LAYOUT_PT, buildInfo);
	m_pModelShader = static_pointer_cast<DefaultShader>(ShaderManager::Instance()->FindOrNew(buildInfo));

	ShaderBuildInfo licbuildInfo;
	licbuildInfo.shaderType = SHADER_TYPE_SSLIC;
	m_pSSLICShader = static_pointer_cast<SSLICShader>(ShaderManager::Instance()->FindOrNew(licbuildInfo));

	TextureData blendTexture;
	blendTexture.width = 256;
	blendTexture.height = 256;
	m_pBlendTexture = make_shared<Texture>();
	m_pBlendTexture->Generate();
	m_pBlendTexture->Begin();
	m_pBlendTexture->Set(blendTexture);
	m_pBlendTexture->End();
}
void SSLICEffect::SetDrawModel(shared_ptr<DefaultVertexBuffer> model)
{
	m_pModel = model;
	if (m_pModel->HasTexCoord() == false)
	{
		Logger::Output(LOG_LEVEL::WARNING, "Need Texcoord.");
	}
}

void SSLICEffect::Draw()
{
	m_pModelShader->Use();
	m_pBlendTexture->Begin();
	m_pModelShader->BindColorTexture();

	m_pModel->Draw();
	
	m_pBlendTexture->End();
	m_pModelShader->UnUse();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC1_ALPHA);
	m_pSSLICShader->Use();
	m_pNoizeTexture->Begin();
	m_pSSLICShader->BindColorTexture();
	m_pPlaneBuffer->Draw();
	m_pNoizeTexture->End();
	m_pSSLICShader->UnUse();
	glDisable(GL_BLEND);

	m_pRenderTarget->CopyColorBuffer(0, m_pBlendTexture.get());
}

void SSLICEffect::Resize(int width, int height)
{

}

}