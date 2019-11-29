namespace KI
{
VectorProperty::VectorProperty(const vector<vec3>& vertexList, const vec3& color)
{
	GenVBO(vertexList, color);
}

VectorProperty::~VectorProperty()
{
}

void VectorProperty::GenVBO(const vector<vec3>& vertexList, const vec3& color)
{
	m_pVertexBuffer = make_shared<DefaultVertexBuffer>();
	m_pVertexBuffer->Generate(VERTEX_LAYOUT::VERTEX_LAYOUT_P);

	m_pVertexBuffer->SetPosition(GL_LINES, vertexList);

	ShaderBuildInfo buildInfo;
	DefaultShader::GetVertexShaderDefine(VERTEX_LAYOUT_P, buildInfo);
	m_pShader = ShaderManager::Instance()->FindOrNew(buildInfo);
}


void VectorProperty::Draw()
{
	m_pShader->Use();
	m_pVertexBuffer->Draw();
	m_pShader->UnUse();
}
}
