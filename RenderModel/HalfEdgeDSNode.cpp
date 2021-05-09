namespace KI
{
namespace RenderModel
{
HalfEdgeDSNode::HalfEdgeDSNode(shared_ptr<HalfEdgeModel> model)
	:PolygonModelNode(static_pointer_cast<IModel>(model)),
	m_pTangentBuffer(nullptr),
	m_pQuadPositionBuffer(nullptr)
{
	//VisibleProperty(PROPERTY_TYPE::PROPERTY_TYPE_VERTEX_INDEX, true);
}

HalfEdgeDSNode::~HalfEdgeDSNode()
{
}

HalfEdgeDSNode* HalfEdgeDSNode::IsHalfEdgeDSNode(IModelNode* pModelNode)
{
	return dynamic_cast<HalfEdgeDSNode*>(pModelNode);
}


shared_ptr<ArrayBuffer> HalfEdgeDSNode::GetTangentBuffer()
{
	if (m_pTangentBuffer == nullptr) {
		m_pTangentBuffer = make_shared<ArrayBuffer>(GL_FLOAT, 3);
	}
	
	return m_pTangentBuffer;
}
shared_ptr<ArrayBuffer> HalfEdgeDSNode::GetQuadPositionBuffer()
{
	if (m_pQuadPositionBuffer == nullptr) {
		m_pQuadPositionBuffer = make_shared<ArrayBuffer>(GL_FLOAT, 3);
	}
	
	return m_pQuadPositionBuffer;
}

void HalfEdgeDSNode::BuildTangentBuffer(const std::vector<vec3>& tangent)
{
	auto pTangentBuffer = GetTangentBuffer();
	if(!pTangentBuffer->IsGenerated()){
		pTangentBuffer->Generate();
	}
	pTangentBuffer->Set(tangent);
}

void HalfEdgeDSNode::BuildQuadPositionBuffer(const std::vector<vec3>& quadPos)
{
	auto pQuadPositionBuffer = GetQuadPositionBuffer();
	if (!pQuadPositionBuffer->IsGenerated()) {
		pQuadPositionBuffer->Generate();
	}
	pQuadPositionBuffer->Set(quadPos);
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

	if (ImGui::Checkbox("Visible BVH", &m_ui.visibleBVH)) {
		VisibleProperty(PROPERTY_TYPE::PROPERTY_TYPE_BVH, m_ui.visibleBVH);
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
}
}
}