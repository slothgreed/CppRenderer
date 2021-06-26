namespace KI
{
namespace RenderModel
{
ResolutionParameterPropertyArgs& ResolutionParameterProperty::DefaultArgs()
{
	static ResolutionParameterPropertyArgs defaultArgs(0,
		(ResolutionParameterPropertyArgs::RESOLUTION_PARAMETER)(
		ResolutionParameterPropertyArgs::RESOLUTION_PARAMETER::COLOR));

	return defaultArgs;
}
ResolutionParameterProperty::ResolutionParameterProperty()
{
	m_buffers.colorVBO = nullptr;
	m_buffers.tangentVBO = nullptr;
	m_buffers.quadVBO = nullptr;
	m_buffers.positionBuffer = nullptr;	// per level.
	m_buffers.normalBuffer = nullptr;
	m_buffers.tangentBuffer = nullptr;
	m_buffers.quadBuffer = nullptr;
	m_buffers.colorData = nullptr;
	m_buffers.tangentData = nullptr;
	m_buffers.quadData = nullptr;
}	
void ResolutionParameterProperty::BuildCore(IModelNode* pModelNode, IPropertyArgs* pPropertyArgs)
{
	assert(pModelNode != nullptr);

	SetModel(pModelNode);

	m_pModel->CalcDownSampling();

	auto pArgs = dynamic_cast<ResolutionParameterPropertyArgs*>(pPropertyArgs);
	if (pArgs == nullptr)
	{
		pArgs = &DefaultArgs();
	}
	
	BuildParameter(pModelNode, pArgs);

}

void ResolutionParameterProperty::Update(IModelNode* pModelNode, IPropertyArgs* pPropertyArgs)
{
	auto pArgs = dynamic_cast<ResolutionParameterPropertyArgs*>(pPropertyArgs);
	if (pArgs == nullptr)
	{
		pArgs = &DefaultArgs();
	}

	UpdateParameter(pModelNode, pArgs);

}

void ResolutionParameterProperty::SetModel(IModelNode* pModelNode)
{
	if (pModelNode->GetModel()->Type() == MODEL_TYPE_HALF_EDGE)
	{
		m_pModel = static_pointer_cast<HalfEdgeModel>(pModelNode->GetModel());
	}
	else
	{
		assert(0);
		return;
	}
}
void ResolutionParameterProperty::GetClusterColor(int level, vector<vec3>& colors)
{
	vector<int> clusterIndex;
	m_pModel->GetDownSampling()->GetCluster(level, clusterIndex);
	int maxIndex = *std::max_element(clusterIndex.begin(), clusterIndex.end());
	colors.resize(clusterIndex.size());

	for (int i = 0; i < colors.size(); i++) {
		colors[i] = m_colorMap[clusterIndex[i]];
	}
}
void ResolutionParameterProperty::Draw(shared_ptr<UniformStruct> pUniform)
{
	if (m_buffers.colorData && m_ui.color.Value()) {
		m_buffers.colorData->Draw(pUniform);
	}
	if (m_buffers.tangentData && m_ui.tangent.Value()) {
		m_buffers.tangentData->Draw(pUniform);
	}
	if (m_buffers.quadData && m_ui.quad.Value()) {
		m_buffers.quadData->Draw(pUniform);
	}

	if (m_buffers.paramData && m_ui.parameterization.Value()) {
		m_buffers.paramData->Draw(pUniform);
	}
}
void ResolutionParameterProperty::InitializeUI()
{
	m_ui.resolution.SetLabel("Level");
	m_ui.resolution.SetMin(0);
	m_ui.resolution.SetValue(0);
	m_ui.resolution.SetMax(m_pModel->GetDownSampling()->GetResolutionNum() - 1);

	m_ui.color.SetLabel("Color");
	m_ui.color.SeValue(false);
	m_ui.tangent.SetLabel("Tangent");
	m_ui.tangent.SeValue(false); 
	m_ui.quad.SetLabel("Quad");
	m_ui.quad.SeValue(false);

	m_ui.parameterization.SetLabel("Parameterization");
	m_ui.parameterization.SeValue(false);

}
void ResolutionParameterProperty::ShowUI()
{
	int parameter = ResolutionParameterPropertyArgs::RESOLUTION_PARAMETER::NONE;
	bool update = false;
	if (m_ui.resolution.Show()) { update = true; }
	if (m_ui.color.Show())		{ update = true; }
	if (m_ui.tangent.Show())	{ update = true; }
	if (m_ui.quad.Show())		{ update = true; }
	if (m_ui.parameterization.Show()) {	update = true;	}

	if (m_ui.color.Value()) {
		parameter |= ResolutionParameterPropertyArgs::RESOLUTION_PARAMETER::COLOR;
	}

	if (m_ui.tangent.Value()) {
		parameter |= ResolutionParameterPropertyArgs::RESOLUTION_PARAMETER::TANGENT;
	}

	if (m_ui.quad.Value()) {
		parameter |= ResolutionParameterPropertyArgs::RESOLUTION_PARAMETER::QUAD;
	}

	if (m_ui.parameterization.Value()) {
		parameter |= ResolutionParameterPropertyArgs::RESOLUTION_PARAMETER::PARAM;
	}

	if (update) {
		BuildParameter(ModelNode(), &ResolutionParameterPropertyArgs(
			m_ui.resolution.Value(),
			(ResolutionParameterPropertyArgs::RESOLUTION_PARAMETER)parameter));
	}
}


void ResolutionParameterProperty::InitializeColorMap(int size)
{
	if (m_colorMap.size() == size) {
		return;
	}

	m_colorMap.resize(size);
	for (int i = 0; i < m_colorMap.size(); i++) {
		m_colorMap[i].x = Gaccho::rnd(0, 255) / 255.0f;
		m_colorMap[i].y = Gaccho::rnd(0, 255) / 255.0f;
		m_colorMap[i].z = Gaccho::rnd(0, 255) / 255.0f;
	}
}
void ResolutionParameterProperty::BuildParameter(IModelNode* pModelNode, ResolutionParameterPropertyArgs* pPropertyArgs)
{
	auto pRenderData = pModelNode->GetRenderData();
	auto pMeshBuffer = pRenderData->GetVertexBuffer();

	if (pPropertyArgs->ParameterType() & ResolutionParameterPropertyArgs::COLOR) {
		InitializeColorMap(pMeshBuffer->GetVertexSize());
	}

	if (pPropertyArgs->ParameterType() & ResolutionParameterPropertyArgs::TANGENT ||
		pPropertyArgs->ParameterType() & ResolutionParameterPropertyArgs::QUAD ||
		pPropertyArgs->ParameterType() & ResolutionParameterPropertyArgs::PARAM) {
		m_pModel->CalcAlignOrientation();
	}

	if (pPropertyArgs->ParameterType() & ResolutionParameterPropertyArgs::QUAD ||
		pPropertyArgs->ParameterType() & ResolutionParameterPropertyArgs::PARAM) {
		m_pModel->CalcArrangePosition();
	}

	if (pPropertyArgs->ParameterType() & ResolutionParameterPropertyArgs::PARAM) {
		auto pNode = HalfEdgeDSNode::IsHalfEdgeDSNode(pModelNode);
		if (pNode) {
			std::vector<vec3> tangent;
			std::vector<vec3> uv;
			shared_ptr<HalfEdgeModel> pModel = static_pointer_cast<HalfEdgeModel>(pModelNode->GetModel());
			pModel->GetDownSampling()->GetData(0, nullptr, nullptr, &tangent, &uv);
			pNode->BuildTangentBuffer(tangent);
			pNode->BuildQuadPositionBuffer(uv);
		}
	}

	UpdateParameter(pModelNode, pPropertyArgs);

}

void ResolutionParameterProperty::UpdateParameter(IModelNode* pModelNode, ResolutionParameterPropertyArgs* pPropertyArgs)
{
	auto pNode = HalfEdgeDSNode::IsHalfEdgeDSNode(pModelNode);
	if (pNode == nullptr) {
		assert(0);
		return;
	}

	if (pPropertyArgs->ParameterType() & ResolutionParameterPropertyArgs::COLOR) {
		vector<vec3> colors;
		GetClusterColor(pPropertyArgs->Level(), colors);
		if (m_buffers.colorVBO == nullptr) {
			m_buffers.colorVBO = make_shared<DefaultVertexBuffer>();
		}
		m_buffers.colorVBO->SetArrayBuffer(VERTEX_ATTRIB::VERTEX_ATTRIB_POSITION, pNode->GetPositionBuffer());
		m_buffers.colorVBO->SetVertexSize(pNode->GetVertexBuffer()->GetVertexSize());
		m_buffers.colorVBO->SetColor(colors);
		m_buffers.colorData = make_shared<RenderData>();
		m_buffers.colorData->SetShading(make_shared<VertexShading>(VERTEX_SHADING_COLOR));
		m_buffers.colorData->SetGeometryData(PRIM_TYPE_TRIANGLES, m_buffers.colorVBO, pNode->GetIndexBuffer());

	}

	if (pPropertyArgs->ParameterType() & ResolutionParameterPropertyArgs::TANGENT ||
		pPropertyArgs->ParameterType() & ResolutionParameterPropertyArgs::QUAD) {

		std::vector<vec3> position;
		std::vector<vec3> normal;
		std::vector<vec3> tangent;
		std::vector<vec3> quad;
		m_pModel->GetDownSampling()->GetData(pPropertyArgs->Level(), &position, &normal, &tangent, &quad);

		if (m_buffers.positionBuffer == nullptr) {
			m_buffers.positionBuffer = make_shared<ArrayBuffer>(GL_FLOAT, 3);
			m_buffers.normalBuffer = make_shared<ArrayBuffer>(GL_FLOAT, 3);
			m_buffers.positionBuffer->Generate();
			m_buffers.normalBuffer->Generate();
		}

		m_buffers.positionBuffer->Set(position);
		m_buffers.normalBuffer->Set(normal);

		if (pPropertyArgs->ParameterType() & ResolutionParameterPropertyArgs::TANGENT) {
			if (m_buffers.tangentVBO == nullptr) {
				m_buffers.tangentVBO = make_shared<VertexBuffer>("Tangent");
				m_buffers.tangentBuffer = make_shared<ArrayBuffer>(GL_FLOAT, 3);
				m_buffers.tangentBuffer->Generate();
				m_buffers.tangentVBO->SetArrayBuffer(TangentVisualizeVertexCode::ATTRIBUTE::POSITION, m_buffers.positionBuffer);
				m_buffers.tangentVBO->SetArrayBuffer(TangentVisualizeVertexCode::ATTRIBUTE::NORMAL, m_buffers.normalBuffer);
				m_buffers.tangentVBO->SetArrayBuffer(TangentVisualizeVertexCode::ATTRIBUTE::TANGENT, m_buffers.tangentBuffer);
				m_buffers.tangentData = make_shared<RenderData>();
				m_buffers.tangentData->SetShading(make_shared<TangentVisualizeShading>(vec4(0, 0, 0, 1), false));
				m_buffers.tangentData->SetGeometryData(PRIM_TYPE::PRIM_TYPE_POINTS, m_buffers.tangentVBO);
			}

			m_buffers.tangentBuffer->Set(tangent);
			m_buffers.tangentVBO->SetVertexSize(position.size());
		}

		if (pPropertyArgs->ParameterType() & ResolutionParameterPropertyArgs::QUAD) {
			if (m_buffers.quadVBO == nullptr) {
				m_buffers.quadVBO = make_shared<VertexBuffer>("Quad");
				m_buffers.quadBuffer = make_shared<ArrayBuffer>(GL_FLOAT, 3);
				m_buffers.quadBuffer->Generate();
				m_buffers.quadVBO->SetArrayBuffer(VERTEX_ATTRIB_POSITION, m_buffers.quadBuffer);
				m_buffers.quadData = make_shared<RenderData>();
				m_buffers.quadData->SetState(make_shared<PointState>(5.0f, true));
				m_buffers.quadData->SetShading(make_shared<BasicShading>(vec4(0, 1, 0, 1)));
				m_buffers.quadData->SetGeometryData(PRIM_TYPE::PRIM_TYPE_POINTS, m_buffers.quadVBO);
			}

			m_buffers.quadBuffer->Set(quad);
			m_buffers.quadVBO->SetVertexSize(position.size());
		}
	}

	if (pPropertyArgs->ParameterType() & ResolutionParameterPropertyArgs::PARAM) {
		if (m_buffers.paramVBO == nullptr) {
			m_buffers.paramVBO = make_shared<VertexBuffer>("Parameterization");
			auto pRenderData = pModelNode->GetRenderData();
			m_buffers.paramVBO->SetVertexSize((GLuint)pRenderData->GetVertexBuffer()->GetVertexSize());
			m_buffers.paramVBO->SetArrayBuffer(MeshParameterizationVertCode::ATTRIBUTE_POSITION, pNode->GetPositionBuffer());
			m_buffers.paramVBO->SetArrayBuffer(MeshParameterizationVertCode::ATTRIBUTE_NORMAL, pNode->GetNormalBuffer());
			m_buffers.paramVBO->SetArrayBuffer(MeshParameterizationVertCode::ATTRIBUTE_TANGENT, pNode->GetTangentBuffer());
			m_buffers.paramVBO->SetArrayBuffer(MeshParameterizationVertCode::ATTRIBUTE_UV, pNode->GetQuadPositionBuffer());

			m_buffers.paramData = make_shared<RenderData>();
			m_buffers.paramData->SetShading(make_shared<MeshParameterizationShading>());
		}

		m_buffers.paramData->SetGeometryData(PRIM_TYPE_TRIANGLES, m_buffers.paramVBO);
		m_buffers.paramData->SetIndexBuffer(PRIM_TYPE_TRIANGLES, pModelNode->GetRenderData()->GetIndexBuffer());
	}
}

}
}