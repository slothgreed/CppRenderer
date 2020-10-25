namespace KI
{
namespace Asset
{
PfxPlane::PfxPlane()
{
	m_pShading = make_shared<OutputShading>();
	Initialize();
}

PfxPlane::~PfxPlane()
{
}

void PfxPlane::Initialize()
{
	m_pRenderData = make_shared<RenderData>();
	ModelGenerator::Plane(m_pRenderData.get(), VERTEX_LAYOUT_TEXCOORD);
	m_pRenderData->SetShading(m_pShading);
}
void PfxPlane::Draw()
{
	assert(m_pShading != nullptr);
	assert(m_pShading->GetTexture() != nullptr);

	m_pRenderData->Draw(nullptr);

	Logger::GLError();
}

void PfxPlane::SetTexture(shared_ptr<Texture> pTexture)
{
	m_pShading->SetTexture(pTexture);
}
}
}
