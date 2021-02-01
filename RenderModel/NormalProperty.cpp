namespace KI
{
namespace RenderModel
{
NormalProperty::NormalProperty()
{
}

NormalProperty::~NormalProperty()
{
}

void NormalProperty::Build(IModelNode* pModelNode, IPropertyArgs* pPropertyArgs)
{
	m_pShading = make_shared<NormalVisualizeShading>();
	m_pShading->SetLength(5.0f);

	m_pRenderData = make_shared<RenderData>();
	m_pRenderData->SetShading(m_pShading);

	SetVBOData(pModelNode);
	InitializeUI();
}

void NormalProperty::Update(IModelNode* pModelNode, IPropertyArgs* pPropertyArgs)
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
	m_pRenderData->SetGeometryData(PRIM_TYPE_POINTS, pVertexBuffer);
}

void NormalProperty::Draw(shared_ptr<UniformStruct> pUniform)
{
	m_pRenderData->Draw(pUniform);
}

void NormalProperty::InitializeUI()
{
	m_ui.length.label = "Length";
	m_ui.length.min = 0.0;
	m_ui.length.value = 0.5;
	m_ui.length.max = 1.0;
}

void NormalProperty::ShowUI()
{
	if (ImGui::SliderFloat(m_ui.length.label.data(), &m_ui.length.value, m_ui.length.min , m_ui.length.max, "%lf", 1.0f)) {
		m_pShading->SetLength(m_ui.length.value);
	}
}

}
}