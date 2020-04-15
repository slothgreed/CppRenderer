namespace KI
{
namespace Renderer
{
PfxPlane::PfxPlane(shared_ptr<IMaterial> material)
{
	m_pMaterial = material;
}

PfxPlane::~PfxPlane()
{
}

void PfxPlane::Initialize()
{
	m_pRenderData = make_shared<RenderData>();
	ModelGenerator::RenderPlane(m_pRenderData.get());
}
void PfxPlane::Draw()
{
	m_pMaterial->Draw(m_pRenderData.get());

	Logger::GLError();
}
}
}
