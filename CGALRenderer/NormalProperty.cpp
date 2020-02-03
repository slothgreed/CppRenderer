namespace KI
{
NormalProperty::NormalProperty()
{
}

NormalProperty::~NormalProperty()
{
}

void NormalProperty::Build(IModel* pModel)
{
	ShaderBuildInfo buildInfo;
	DefaultShader::GetVertexShaderDefine(VERTEX_LAYOUT_P, buildInfo);
	m_pShader = ShaderManager::Instance()->FindOrNew(buildInfo);


	m_pVertexBuffer = make_shared<DefaultVertexBuffer>();
	m_pVertexBuffer->Generate(VERTEX_LAYOUT::VERTEX_LAYOUT_P);

	SetVBOData(pModel);
}

void NormalProperty::Update(IModel* pModel)
{
	SetVBOData(pModel);
}

void NormalProperty::SetVBOData(IModel* pModel)
{
	vector<Vertex> vertexList;
	pModel->GetVertexList(vertexList);
	vector<vec3> normalList;
	for (int i = 0; i < vertexList.size(); i++)
	{
		normalList.push_back(vertexList[i].Position());
		normalList.push_back(vertexList[i].Position() + vertexList[i].Normal());
	}

	m_pVertexBuffer->SetPosition(GL_LINES, normalList);
}

void NormalProperty::Draw()
{
	m_pShader->Use();
	m_pVertexBuffer->Draw();
	m_pShader->UnUse();
}
}
