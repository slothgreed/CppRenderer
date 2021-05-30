
namespace KI
{
namespace RenderModel
{

SDFProperty::SDFProperty()
{
}

SDFProperty::~SDFProperty()
{
}

void SDFProperty::BuildCore(IModelNode* pModel, IPropertyArgs* pPropertyArgs)
{
	auto pHalfEdgeNode = HalfEdgeDSNode::IsHalfEdgeDSNode(pModel);
	if (!pHalfEdgeNode) {
		assert(0);
		return;
	}

	auto pHalfEdgeModel = dynamic_cast<HalfEdgeModel*>(pHalfEdgeNode->GetModel());
	if (!pHalfEdgeModel) {
		assert(0);
		return;
	}
	
	pHalfEdgeModel->CalcShapeDiameter();
	std::vector<float> sdfValue = pHalfEdgeModel->GetShapeDiameterValue();
	float maxValue = std::numeric_limits<float>::min();
	float minValue = std::numeric_limits<float>::max();
	std::vector<vec3> pseudoColor(sdfValue.size());
	for (int i = 0; sdfValue.size(); i++) {
		maxValue = std::max(maxValue, sdfValue[i]);
		minValue = std::max(minValue, sdfValue[i]);
	}

	for (int i = 0; i < pseudoColor.size(); i++)
	{
		pseudoColor[i] = ColorUtility::GetPseudoColor(sdfValue[i], minValue, maxValue);
	}

	if (m_pRenderData == nullptr) {
		m_pRenderData = make_shared<RenderData>();
		m_sdfBuffer = make_shared<DefaultVertexBuffer>();
	}
	m_sdfBuffer->SetArrayBuffer(VERTEX_ATTRIB_POSITION, pHalfEdgeNode->GetPositionBuffer());
	m_sdfBuffer->SetColor(pseudoColor);

	m_pRenderData->SetGeometryData(PRIM_TYPE::PRIM_TYPE_TRIANGLES, m_sdfBuffer, pHalfEdgeNode->GetIndexBuffer());
}
void SDFProperty::Update(IModelNode* pModel, IPropertyArgs* pPropertyArgs)
{

}

void SDFProperty::Draw(shared_ptr<UniformStruct> pUniform)
{
	m_pRenderData->Draw(pUniform);
}
}
}