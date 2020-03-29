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
	m_pUniform = make_shared<DefaultUniform>();
	m_pUniform->SetFixColor(vec4(0, 0, 1, 1));

	m_pVertexBuffer = make_shared<DefaultVertexBuffer>();
	auto pBuildInfo = make_shared<IShaderBuildInfo>(SHADER_TYPE::SHADER_TYPE_DEFAULT);
	auto pVertexCode = make_shared<DefaultVertexCode>();
	pVertexCode->SetShaderDefine(m_pVertexBuffer->Layout());
	pBuildInfo->SetVertexCode(pVertexCode);
	pBuildInfo->SetFragCode(make_shared<DefaultFragCode>());
	m_pShader = ShaderManager::Instance()->FindOrNew(pBuildInfo);

	SetVBOData(pModel);
}

void NormalProperty::Update(IModel* pModel)
{
	SetVBOData(pModel);
}

void NormalProperty::SetVBOData(IModel* pModel)
{
	vector<Vertex> vertexList;
	IPolygonModel* pPolygonModel = nullptr;
	if (IPolygonModel::IsPolygonModel(pModel->Type()))
	{
		pPolygonModel = (IPolygonModel*)pModel;
	}
	else
	{
		assert(0);
	}

	pPolygonModel->GetVertexList(vertexList);
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
	m_pShader->Bind(m_pUniform);
	m_pVertexBuffer->Draw();
	m_pShader->UnBind();
	m_pShader->UnUse();
}
}
