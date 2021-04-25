
namespace KI
{
namespace RenderModel
{
QuadPositionProperty::QuadPositionProperty()
	:m_pointSize(5.0f)
{
}

QuadPositionProperty::~QuadPositionProperty()
{

}

void QuadPositionProperty::BuildCore(IModelNode* pModelNode, IPropertyArgs* pPropertyArgs)
{
	m_pShading = make_shared<BasicShading>(vec4(1, 0, 0, 1));

	m_pRenderData = make_shared<RenderData>();
	m_pRenderData->SetShading(m_pShading);

	Update(pModelNode, pPropertyArgs);
}

void QuadPositionProperty::Update(IModelNode* pModelNode, IPropertyArgs* pPropertyArgs)
{
	if (pPropertyArgs == nullptr) {
		SetVBOData(pModelNode, &QuadPositionPropertyArgs(0));
	}
	else if(pPropertyArgs->Type() == PROPERTY_TYPE_QUAD_POSITION){
		SetVBOData(pModelNode, static_cast<QuadPositionPropertyArgs*>(pPropertyArgs));
	}
}

void QuadPositionProperty::SetVBOData(IModelNode* pModelNode, QuadPositionPropertyArgs* pPropertyArgs)
{
	vector<Vertex> vertexList;
	shared_ptr<HalfEdgeModel> pModel = GetHalfEdgeModel();
	
	if (m_pVertexBuffer == nullptr) {
		m_pVertexBuffer = make_shared<DefaultVertexBuffer>("Position");
	}


	std::vector<vec3> quadPos;
	pModel->GetDownSampling()->GetData(pPropertyArgs->Level(), nullptr, nullptr, nullptr, &quadPos);
	m_pVertexBuffer->SetPosition(quadPos);

	m_pRenderData->SetGeometryData(PRIM_TYPE_POINTS, m_pVertexBuffer);
}

void QuadPositionProperty::Draw(shared_ptr<UniformStruct> pUniform)
{
	glPointSize(m_pointSize);
	m_pRenderData->Draw(pUniform);
}


shared_ptr<HalfEdgeModel> QuadPositionProperty::GetHalfEdgeModel()
{
	if (ModelNode()->GetModel()->Type() == MODEL_TYPE_HALF_EDGE)
	{
		return static_pointer_cast<HalfEdgeModel>(ModelNode()->GetModel());
	}
	else
	{
		assert(0);
		return nullptr;
	}
}

void QuadPositionProperty::InitializeUI()
{

	m_ui.pointSize.SetLabel("Quad Point Size");
	m_ui.pointSize.SetMin(0.0);
	m_ui.pointSize.SetMax(1.0);
	m_ui.pointSize.SetValue(m_pointSize);

	m_ui.level.SetLabel("Quad Point Level");
	m_ui.level.SetMin(0);
	m_ui.level.SetMax(GetHalfEdgeModel()->GetDownSampling()->GetResolutionNum() - 1);
	m_ui.level.SetValue(0);
}

void QuadPositionProperty::ShowUI()
{
	if (m_ui.pointSize.Show()) {
		m_pointSize = m_ui.pointSize.Value();
	}

	if (m_ui.level.Show()) {
		SetVBOData(ModelNode(), &QuadPositionPropertyArgs(m_ui.level.Value()));
	}
}

}
}