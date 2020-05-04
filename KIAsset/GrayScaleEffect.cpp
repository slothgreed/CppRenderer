namespace KI
{
namespace Asset
{
GrayScaleEffect::GrayScaleEffect()
{
}

GrayScaleEffect::~GrayScaleEffect()
{
}

void GrayScaleEffect::Initialize(int width, int height)
{
	m_pPlane = make_shared<RenderData>();
	ModelGenerator::Plane(m_pPlane.get(), VERTEX_LAYOUT_TEXCOORD);

	auto pBuildInfo = make_shared<IShaderBuildInfo>(SHADER_TYPE::SHADER_TYPE_GRAYSCALE);
	pBuildInfo->SetVertexCode(make_shared<PostProcessVertexCode>());
	pBuildInfo->SetFragCode(make_shared<GrayScaleFragCode>());
	auto pGrayScaleShader = static_pointer_cast<GrayScaleShader>(ShaderManager::Instance()->FindOrNew(pBuildInfo));
	m_pRenderTarget = make_shared<RenderTarget>();
	m_pRenderTarget->Initialize(1, width, height);

	auto pGrayMaterial = make_shared<GeneralMaterial>();
	pGrayMaterial->SetShader(pGrayScaleShader);
	pGrayMaterial->GetUniform()->Set(nullptr, make_shared<GrayScaleUniform>());

	m_pPlane->SetMaterial(pGrayMaterial);
}

void GrayScaleEffect::SetTexture(shared_ptr<Texture> pTexture)
{
	if (m_pPlane->GetMaterial()->GetUniform()->Frag()->Type() != SHADER_TYPE::SHADER_TYPE_GRAYSCALE) {
		assert(0);
		return;
	}

	auto uniformParameter = static_pointer_cast<GrayScaleUniform>(m_pPlane->GetMaterial()->GetUniform()->Frag());

	uniformParameter->SetTexture(pTexture);
}

void GrayScaleEffect::Resize(int width, int height)
{
	m_pRenderTarget->Resize(width, height);
}
void GrayScaleEffect::Draw()
{
	m_pRenderTarget->Begin();
	m_pRenderTarget->Clear();
	m_pPlane->Draw();
	m_pRenderTarget->End();
}

//void GrayScaleEffect::ReadFromXML(const boost::property_tree::ptree& tree)
//{
//
//}
//
//
//void GrayScaleEffect::WriteToXML(const boost::property_tree::ptree& tree)
//{
//
//}

}
}