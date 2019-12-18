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
	vector<vec3> position;
	position.reserve(4);
	position.push_back(vec3(-1, -1, 0));
	position.push_back(vec3(1, -1, 0));
	position.push_back(vec3(-1, 1, 0));
	position.push_back(vec3(1, 1, 0));

	vector<vec2> texcoord;
	texcoord.push_back(vec2(0, 0));
	texcoord.push_back(vec2(1, 0));
	texcoord.push_back(vec2(0, 1));
	texcoord.push_back(vec2(1, 1));

	auto vertexBuffer = make_shared<DefaultVertexBuffer>();
	vertexBuffer->Generate(VERTEX_LAYOUT_PT);
	vertexBuffer->SetPosition(GL_TRIANGLE_STRIP, position);
	vertexBuffer->SetTexcoord(texcoord);


	m_pMaterial->SetVertexBuffer(vertexBuffer);
	m_pMaterial->CompileShader();

}
void PfxPlane::Draw()
{
	m_pMaterial->Draw();

	Logger::GLError();
}


}
