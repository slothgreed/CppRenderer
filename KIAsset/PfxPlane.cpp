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
	if (m_pShading == nullptr ||
		m_pShading->GetTexture() == nullptr)
	{
		assert(0);
		return;
	}
	m_pRenderData->Draw(nullptr);

	Logger::GLError();
}

void PfxPlane::SetTexture(shared_ptr<Texture> pTexture)
{
	m_pShading->SetTexture(pTexture);
}
}
}
