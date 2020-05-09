namespace KI
{
namespace Renderer
{
PfxPlane::PfxPlane(shared_ptr<IShaderPass> pShaderPass)
{
	m_pShaderPass = pShaderPass;
}

PfxPlane::~PfxPlane()
{
}

void PfxPlane::Initialize()
{
	m_pRenderData = make_shared<RenderData>();
	ModelGenerator::Plane(m_pRenderData.get(), VERTEX_LAYOUT_TEXCOORD);
	m_pRenderData->SetShaderPass(m_pShaderPass);
}
void PfxPlane::Draw()
{
	m_pRenderData->Draw();

	Logger::GLError();
}
}
}
