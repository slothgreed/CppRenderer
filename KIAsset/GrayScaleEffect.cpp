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

	m_pMaterial = make_shared<GrayScaleMaterial>();

	m_pRenderTarget = make_shared<RenderTarget>();
	m_pRenderTarget->Initialize(1, width, height);

	m_pPlane->SetMaterial(m_pMaterial);
}

void GrayScaleEffect::SetTexture(shared_ptr<Texture> pTexture)
{
	m_pMaterial->SetTexture(pTexture);
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

}
}