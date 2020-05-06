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
	auto pGeomUniform = make_shared<NormalVisualizeUniform>();
	pGeomUniform->SetLength(5.0f);

	auto pBuildInfo = make_shared<IShaderBuildInfo>(SHADER_TYPE::SHADER_TYPE_NORMALVISUALIZE);
	auto pVertexCode = make_shared<DefaultVertexCode>();
	auto pFragCode = make_shared<DefaultFragCode>();
	pVertexCode->SetShaderDefine(SHADER_TYPE::SHADER_TYPE_NORMALVISUALIZE);
	pFragCode->SetShaderDefine(SHADER_TYPE::SHADER_TYPE_NORMALVISUALIZE);

	pBuildInfo->SetVertexCode(pVertexCode);
	pBuildInfo->SetGeomCode(make_shared<NormalVisualizeGeometryCode>());
	pBuildInfo->SetFragCode(pFragCode);
	auto pShader = ShaderManager::Instance()->FindOrNew(pBuildInfo);

	m_pRenderData = make_shared<RenderData>();
	auto pMaterial = make_shared<GeneralShaderPass>();
	pMaterial->SetShader(pShader);
	pMaterial->GetUniform()->Set(nullptr, pGeomUniform, nullptr);
	m_pRenderData->SetMaterial(pMaterial);

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
		return;
	}

	auto pVertexBuffer = pPolygonModel->GetVertexBuffer();
	m_pRenderData->SetGeometryData(GL_POINTS, pVertexBuffer);
}

void NormalProperty::Draw()
{
	m_pRenderData->Draw();
}
}
