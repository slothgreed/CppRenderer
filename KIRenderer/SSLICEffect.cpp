namespace KI
{
namespace Renderer
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
	ModelGenerator::RenderPlane(m_pPlaneData.get());

	TextureData blendTexture;
	blendTexture.width = 256;
	blendTexture.height = 256;
	m_pBlendTexture = make_shared<Texture>();
	m_pBlendTexture->Generate();
	m_pBlendTexture->Begin();
	m_pBlendTexture->Set(blendTexture);
	m_pBlendTexture->End();

	auto pVertexUniform = make_shared<DefaultVertexUniform>();
	auto pFragUniform = make_shared<DefaultFragUniform>();
	pFragUniform->SetTexture(m_pBlendTexture);
	m_pModelUniform = make_shared<UniformSet>();
	m_pModelUniform->Set(pVertexUniform, pFragUniform);


	auto pSSLICVertexUniform = make_shared<DefaultVertexUniform>();
	auto pSSLICFragUniform = make_shared<DefaultFragUniform>();
	pSSLICFragUniform->SetTexture(m_pBlendTexture);
	m_pSSLICUniform = make_shared<UniformSet>();
	m_pModelUniform->Set(pSSLICVertexUniform, pSSLICFragUniform);

	auto pBuildInfo = make_shared<IShaderBuildInfo>(SHADER_TYPE_DEFAULT);
	auto pVertexCode = make_shared<DefaultVertexCode>();
	
	auto pPlaneBuffer = m_pPlaneData->GetVertexBuffer();
	if (pPlaneBuffer->Type() == VERTEX_BUFFER_TYPE_DEFAULT)
	{
		auto pDefaultBuffer = static_pointer_cast<DefaultVertexBuffer>(pPlaneBuffer);
		pVertexCode->SetShaderDefine(pDefaultBuffer->Layout());
	}


	pBuildInfo->SetVertexCode(pVertexCode);
	pBuildInfo->SetFragCode(make_shared<DefaultFragCode>());
	m_pModelShader = static_pointer_cast<DefaultShader>(ShaderManager::Instance()->FindOrNew(pBuildInfo));


	auto pSSLICInfo = make_shared<IShaderBuildInfo>(SHADER_TYPE_SSLIC);
	pSSLICInfo->SetVertexCode(make_shared<PostProcessVertexCode>());
	pSSLICInfo->SetFragCode(make_shared<SSLICFragCode>());

	m_pSSLICShader = static_pointer_cast<SSLICShader>(ShaderManager::Instance()->FindOrNew(pSSLICInfo));
}
void SSLICEffect::SetRenderData(shared_ptr<RenderData> pRenderData)
{
	m_pModelData = pRenderData;
}

void SSLICEffect::Draw()
{
	m_pModelShader->Use();
	m_pModelShader->Bind(m_pModelUniform);

	m_pModelData->Draw();

	m_pModelShader->UnBind(m_pModelUniform);
	m_pModelShader->UnUse();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC1_ALPHA);
	m_pSSLICShader->Use();
	m_pSSLICShader->Bind(m_pSSLICUniform);
	m_pPlaneData->Draw();
	m_pSSLICShader->UnBind(m_pSSLICUniform);
	m_pSSLICShader->UnUse();
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