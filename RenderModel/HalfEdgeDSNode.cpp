namespace KI
{
namespace RenderModel
{
HalfEdgeDSNode::HalfEdgeDSNode(shared_ptr<HalfEdgeModel> model)
	:PolygonModelNode(static_pointer_cast<IModel>(model))
{
	VisibleProperty(PROPERTY_TYPE::PROPERTY_TYPE_RESOLUTION, true);
	VisibleProperty(PROPERTY_TYPE::PROPERTY_TYPE_VERTEX_TANGENT, true);
	auto pModel = ((HalfEdgeModel*)m_pModel.get());
	auto pProperty = GetProperty(PROPERTY_TYPE::PROPERTY_TYPE_VERTEX_TANGENT);
	pProperty->Update(this, nullptr);
	//VisibleProperty(PROPERTY_TYPE::PROPERTY_TYPE_VERTEX_INDEX, true);
}

HalfEdgeDSNode::~HalfEdgeDSNode()
{
}

void HalfEdgeDSNode::ShowUI()
{
	PolygonModelNode::ShowUI();
	if (ImGui::Checkbox("Visible HalfEdgeLine", &m_ui.visibleHalfEdge)) {
		VisibleProperty(PROPERTY_TYPE::PROPERTY_TYPE_HALFEDGE, m_ui.visibleHalfEdge);
	}

	if (ImGui::Checkbox("Visible Resolution", &m_ui.visibleResolution)) {
		VisibleProperty(PROPERTY_TYPE::PROPERTY_TYPE_RESOLUTION, m_ui.visibleResolution);
	}

	if (ImGui::Checkbox("Visible Tangent", &m_ui.visibleTangent)) {
		VisibleProperty(PROPERTY_TYPE::PROPERTY_TYPE_VERTEX_TANGENT, m_ui.visibleTangent);
	}

	if (ImGui::Checkbox("Visible BVH", &m_ui.visibleBVH)) {
		VisibleProperty(PROPERTY_TYPE::PROPERTY_TYPE_BVH, m_ui.visibleBVH);
	}

	if (ImGui::SmallButton("Calc Alignment")) {
		auto pModel = ((HalfEdgeModel*)m_pModel.get());
		pModel->CalcAlignOrientation();
		auto pProperty = GetProperty(PROPERTY_TYPE::PROPERTY_TYPE_VERTEX_TANGENT);
		pProperty->Update(this, nullptr);
	}

	if (ImGui::SmallButton("Arrange Position")) {
		auto pModel = ((HalfEdgeModel*)m_pModel.get());
		//if (pModel->CalcArrangePosition())
		{
			VisibleProperty(PROPERTY_TYPE::PROPERTY_TYPE_QUAD_POSITION, true);
			VisibleProperty(PROPERTY_TYPE::PROPERTY_TYPE_MESH_PARAMETERIZATION, true);
		}
	}

	if (ImGui::Checkbox("Vertex Index", &m_ui.visibleIndex)) {
		VisibleProperty(PROPERTY_TYPE::PROPERTY_TYPE_VERTEX_INDEX, m_ui.visibleIndex);
	}

	PropertyIterator itr(this);
	for (; itr.HasNext(); itr.Next()) {
		auto pProperty = dynamic_cast<IRenderModelProperty*>(itr.Current());
		if (pProperty)
			pProperty->ShowUI();
	}

	auto pModel = ((HalfEdgeModel*)m_pModel.get());

	m_ui.plot.Show(pModel->GetOrientationError());
	auto pProperty = GetProperty(PROPERTY_TYPE::PROPERTY_TYPE_QUAD_POSITION);
	if (pProperty != nullptr) {
		//m_ui.plot.Show(pModel->GetPositionError());
	}


}
}
}