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
	m_pVertexBuffer = make_shared<DefaultVertexBuffer>();
	ModelGenerator::RenderPlane(m_pVertexBuffer.get());
}
void PfxPlane::Draw()
{
	m_pMaterial->Draw(m_pVertexBuffer.get());

	Logger::GLError();
}
}
}
