namespace KI
{
namespace Renderer
{
PfxPlane::PfxPlane(shared_ptr<IMaterial> pMaterial)
{
	m_pMaterial = pMaterial;
}

PfxPlane::~PfxPlane()
{
}

void PfxPlane::Initialize()
{
	m_pRenderData = make_shared<RenderData>();
	ModelGenerator::RenderPlane(m_pRenderData.get());
	m_pRenderData->SetMaterial(m_pMaterial);
}
void PfxPlane::Draw()
{
	m_pRenderData->Draw();

	Logger::GLError();
}
}
}
