namespace KI
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
	auto vertexBuffer = make_shared<DefaultVertexBuffer>();
	ModelGenerator::RenderPlane(vertexBuffer.get());

	m_pMaterial->SetVertexBuffer(vertexBuffer);
	m_pMaterial->CompileShader();

}
void PfxPlane::Draw()
{
	m_pMaterial->Draw();

	Logger::GLError();
}


}
