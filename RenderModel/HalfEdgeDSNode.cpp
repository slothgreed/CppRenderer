namespace KI
{
namespace RenderModel
{
HalfEdgeDSNode::HalfEdgeDSNode(shared_ptr<HalfEdgeModel> model)
	:PolygonModelNode(static_pointer_cast<IModel>(model))
{
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

	PropertyIterator itr(this);
	for (; itr.HasNext(); itr.Next()) {
		auto pProperty = dynamic_cast<IRenderModelProperty*>(itr.Current());
		if (pProperty)
			pProperty->ShowUI();
	}

}
}
}