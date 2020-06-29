namespace KI
{
namespace Renderer
{
PfxPlane::PfxPlane(shared_ptr<IShading> pShading)
{
	m_pShading = pShading;
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
	m_pRenderData->Draw();

	Logger::GLError();
}
}
}
