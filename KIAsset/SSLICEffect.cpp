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

	m_pModelMaterial = make_shared<DefaultShaderPass>();
	m_pModelMaterial->AddTexture(m_pBlendTexture);


	auto pSSLICMaterial = make_shared<GeneralShaderPass>();
	auto pSSLICInfo = make_shared<IShaderBuildInfo>(SHADER_TYPE_SSLIC);
	pSSLICInfo->SetVertexCode(make_shared<PostProcessVertexCode>());
	pSSLICInfo->SetFragCode(make_shared<SSLICFragCode>());

	auto pSSLICShader = static_pointer_cast<SSLICShader>(ShaderManager::Instance()->FindOrNew(pSSLICInfo));
	
	pSSLICMaterial->SetShader(pSSLICShader);
	m_pPlaneData->SetMaterial(pSSLICMaterial);
}
void SSLICEffect::SetRenderData(shared_ptr<RenderData> pRenderData)
{
	m_pModelData = pRenderData->Clone();
	m_pModelData->SetMaterial(m_pModelMaterial);
}

void SSLICEffect::Draw()
{
	m_pModelData->Draw();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC1_ALPHA);
	m_pPlaneData->Draw();
	glDisable(GL_BLEND);

	m_pRenderTarget->CopyColorBuffer(0, m_pBlendTexture.get());
}

void SSLICEffect::Resize(int width, int height)
{

}


//void SSLICEffect::ReadFromXML(const boost::property_tree::ptree& tree)
//{
//
//}
//
//
//void SSLICEffect::WriteToXML(const boost::property_tree::ptree& tree)
//{
//
//}

}
}