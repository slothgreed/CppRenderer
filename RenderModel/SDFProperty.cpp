
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
	auto pSDF = pHalfEdgeModel->GetShapeDiameterFunction();


	//if (m_pRayBuffer == nullptr) {
	//	m_pRayData = make_shared<RenderData>();
	//	m_pRayBuffer = make_shared<DefaultVertexBuffer>();
	//	m_pPointSampleData = make_shared<RenderData>();
	//	m_pPointSampleBuffer = make_shared<DefaultVertexBuffer>();
	//	m_pTriangleData = make_shared<RenderData>();
	//	m_pTriangleBuffer = make_shared<DefaultVertexBuffer>();
	//}
	//vector<vec3> rayPositions;
	//vec3 dir = vec3(pSDF->GetRay().Direction().z * 10, pSDF->GetRay().Direction().y * 10, pSDF->GetRay().Direction().z * 10);
	//rayPositions.push_back(pSDF->GetRay().Origin() - dir);
	//rayPositions.push_back(pSDF->GetRay().Origin() + dir);
	//m_pRayBuffer->SetPosition(rayPositions);
	//m_pRayData->SetShading(make_shared<BasicShading>(vec4(1.0, 0.0, 1.0,1.0)));
	//m_pRayData->SetGeometryData(PRIM_TYPE::PRIM_TYPE_LINES, m_pRayBuffer);

	//m_pPointSampleBuffer->SetPosition(pSDF->GetTestPos());
	//m_pPointSampleData->SetShading(make_shared<BasicShading>(vec4(1.0, 0.0, 0.0, 1.0)));
	//m_pPointSampleData->SetGeometryData(PRIM_TYPE::PRIM_TYPE_POINTS, m_pPointSampleBuffer);

	//vector<vec3> pos(3);
	//pSDF->GetTri().GetPosition(&pos[0], &pos[1], &pos[2]);
	//m_pTriangleBuffer->SetPosition(pos);
	//m_pTriangleData->SetShading(make_shared<BasicShading>(vec4(1.0, 0.0, 1.0, 1.0)));
	//m_pTriangleData->SetGeometryData(PRIM_TYPE::PRIM_TYPE_TRIANGLES, m_pTriangleBuffer);

	float maxValue = std::numeric_limits<float>::min();
	float minValue = std::numeric_limits<float>::max();
	std::vector<vec3> pseudoColor(sdfValue.size());
	for (int i = 0; i < sdfValue.size(); i++) {
		maxValue = std::max(maxValue, sdfValue[i]);
		minValue = std::min(minValue, sdfValue[i]);
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
	m_pRenderData->SetShading(make_shared<VertexShading>(VERTEX_SHADING_TYPE::VERTEX_SHADING_COLOR));
	m_pRenderData->SetGeometryData(PRIM_TYPE::PRIM_TYPE_TRIANGLES, m_sdfBuffer, pHalfEdgeNode->GetIndexBuffer());
}
void SDFProperty::Update(IModelNode* pModel, IPropertyArgs* pPropertyArgs)
{

}

void SDFProperty::Draw(shared_ptr<UniformStruct> pUniform)
{
	//glPointSize(5);
	//m_pPointSampleData->Draw(pUniform);
	//m_pRayData->Draw(pUniform);
	//m_pTriangleData->Draw(pUniform);
	m_pRenderData->Draw(pUniform);
}
}
}