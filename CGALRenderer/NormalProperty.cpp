namespace KI
{
NormalProperty::NormalProperty()
{
}

NormalProperty::~NormalProperty()
{
}

void NormalProperty::Build(IModelNode* pModelNode)
{
	m_pUniform = make_shared<NormalVisualizeUniform>();
	m_pUniform->SetLength(5.0f);

	auto pBuildInfo = make_shared<IShaderBuildInfo>(SHADER_TYPE::SHADER_TYPE_NORMALVISUALIZE);
	auto pVertexCode = make_shared<DefaultVertexCode>();
	auto pFragCode = make_shared<DefaultFragCode>();
	pVertexCode->SetShaderDefine(SHADER_TYPE::SHADER_TYPE_NORMALVISUALIZE);
	pFragCode->SetShaderDefine(SHADER_TYPE::SHADER_TYPE_NORMALVISUALIZE);

	pBuildInfo->SetVertexCode(pVertexCode);
	pBuildInfo->SetGeomCode(make_shared<NormalVisualizeGeometryCode>());
	pBuildInfo->SetFragCode(pFragCode);
	m_pShader = ShaderManager::Instance()->FindOrNew(pBuildInfo);

	SetVBOData(pModelNode);
}

void NormalProperty::Update(IModelNode* pModelNode)
{
	SetVBOData(pModelNode);
}

void NormalProperty::SetVBOData(IModelNode* pModelNode)
{
	vector<Vertex> vertexList;
	PolygonModelNode* pPolygonModel = nullptr;
	if (IPolygonModel::IsPolygonModel(pModelNode->GetModel()->Type()))
	{
		pPolygonModel = (PolygonModelNode*)pModelNode;
	}
	else
	{
		assert(0);
	}

	m_pVertexBuffer = pPolygonModel->GetVertexBuffer();
}

void NormalProperty::Draw()
{
	m_pShader->Use();
	m_pShader->Bind(m_pUniform);
	m_pVertexBuffer->Draw(GL_POINTS, 0, m_pVertexBuffer->GetVertexSize());
	m_pShader->UnBind(m_pUniform);
	m_pShader->UnUse();
}
}
