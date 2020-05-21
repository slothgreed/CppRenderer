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
	m_pMaterial = make_shared<NormalVisualizeMaterial>();
	m_pMaterial->SetLength(5.0f);

	m_pRenderData = make_shared<RenderData>();
	m_pRenderData->SetMaterial(m_pMaterial);

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
