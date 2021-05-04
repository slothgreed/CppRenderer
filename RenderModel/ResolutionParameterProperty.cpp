namespace KI
{
namespace RenderModel
{
ResolutionParameterPropertyArgs& ResolutionParameterProperty::DefaultArgs()
{
	static ResolutionParameterPropertyArgs defaultArgs(0);

	return defaultArgs;
}
ResolutionParameterProperty::ResolutionParameterProperty()
{
	m_pRenderData = nullptr;
	m_pTangentBuffer = nullptr;
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
	if (pArgs->ParameterType() & ResolutionParameterPropertyArgs::RESOLUTION_PARAMETER::COLOR)
	{
		BuildColor(pModelNode, pArgs);
	}
	else if (pArgs->ParameterType() & ResolutionParameterPropertyArgs::RESOLUTION_PARAMETER::TANGENT) {

		BuildTangent(pModelNode, pArgs);
	}

	BuildTangent(pModelNode, pArgs);

}

void ResolutionParameterProperty::Update(IModelNode* pModelNode, IPropertyArgs* pPropertyArgs)
{
	auto pArgs = dynamic_cast<ResolutionParameterPropertyArgs*>(pPropertyArgs);
	if (pArgs == nullptr)
	{
		pArgs = &DefaultArgs();
	}

	if (pArgs->ParameterType() & ResolutionParameterPropertyArgs::RESOLUTION_PARAMETER::COLOR)
	{
		UpdateColor(pModelNode, pArgs);
	} else if (pArgs->ParameterType() & ResolutionParameterPropertyArgs::RESOLUTION_PARAMETER::TANGENT) {
		UpdateTangent(pModelNode, pArgs);
	}

	UpdateTangent(pModelNode, pArgs);

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
void ResolutionParameterProperty::GetClusterColor(ResolutionParameterPropertyArgs* pPropertyArgs, vector<vec3>& colors)
{
	auto pDownSampling = m_pModel->GetDownSampling();
	if (pDownSampling == nullptr)
	{
		assert(0);
		return;
	}

	vector<int> clusterIndex;
	pDownSampling->GetCluster(pPropertyArgs->m_level, clusterIndex);
	int maxIndex = *std::max_element(clusterIndex.begin(), clusterIndex.end());
	colors.resize(clusterIndex.size());

	for (int i = 0; i < colors.size(); i++) {
		colors[i] = m_colorMap[clusterIndex[i]];
	}
}
void ResolutionParameterProperty::Draw(shared_ptr<UniformStruct> pUniform)
{
	m_pRenderData->Draw(pUniform);
}
void ResolutionParameterProperty::InitializeUI()
{
	m_ui.resolution.SetLabel("Level");
	m_ui.resolution.SetMin(0);
	m_ui.resolution.SetValue(0);
	m_ui.resolution.SetMax(m_pModel->GetDownSampling()->GetResolutionNum() - 1);

}
void ResolutionParameterProperty::ShowUI()
{
	if (m_ui.resolution.Show()) {
		Update(nullptr, &ResolutionParameterPropertyArgs(m_ui.resolution.Value()));
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
void ResolutionParameterProperty::BuildColor(IModelNode* pModelNode, ResolutionParameterPropertyArgs* pPropertyArgs)
{
	auto pRenderData = pModelNode->GetRenderData(0);
	auto pMeshBuffer = pRenderData->GetVertexBuffer();
	m_pRenderData = make_shared<RenderData>();
	InitializeColorMap(pMeshBuffer->GetVertexSize());
	vector<vec3> colors;
	GetClusterColor(pPropertyArgs, colors);

	auto pVertexBuffer = make_shared<DefaultVertexBuffer>();
	pVertexBuffer->SetArrayBuffer(VERTEX_ATTRIB::VERTEX_ATTRIB_POSITION, pMeshBuffer->GetArrayBuffer(VERTEX_ATTRIB::VERTEX_ATTRIB_POSITION));
	pVertexBuffer->SetVertexSize(pMeshBuffer->GetVertexSize());
	pVertexBuffer->SetColor(colors);
	m_pRenderData->SetGeometryData(PRIM_TYPE_TRIANGLES, pVertexBuffer, pRenderData->GetIndexBuffer());

	m_pRenderData->SetShading(make_shared<VertexShading>(VERTEX_SHADING_COLOR));
}

void ResolutionParameterProperty::UpdateColor(IModelNode* pModelNode, ResolutionParameterPropertyArgs* pPropertyArgs)
{
	vector<vec3> colors;
	GetClusterColor(pPropertyArgs, colors);
	auto pVertexBuffer = m_pRenderData->GetVertexBuffer();
	if (pVertexBuffer->Type() == VERTEX_BUFFER_TYPE_DEFAULT)
	{
		auto pDefaultBuffer = static_pointer_cast<DefaultVertexBuffer>(pVertexBuffer);
		pDefaultBuffer->SetColor(colors);
	}
	else
	{
		assert(0);
	}
}

void ResolutionParameterProperty::BuildTangent(IModelNode* pModelNode, ResolutionParameterPropertyArgs* pPropertyArgs)
{
	
	if (m_pTangentBuffer == nullptr) {
		auto pRenderData = pModelNode->GetRenderData(0);
		auto pMeshBuffer = pRenderData->GetVertexBuffer();
		auto pVertexBuffer = make_shared<VertexBuffer>("Tangent");
		pVertexBuffer->SetArrayBuffer(TangentVisualizeVertexCode::ATTRIBUTE::POSITION, pMeshBuffer->GetArrayBuffer(VERTEX_ATTRIB_POSITION));
		pVertexBuffer->SetArrayBuffer(TangentVisualizeVertexCode::ATTRIBUTE::NORMAL, pMeshBuffer->GetArrayBuffer(VERTEX_ATTRIB_NORMAL));
		pVertexBuffer->SetVertexSize(pMeshBuffer->GetVertexSize());
		m_pTangentBuffer = make_shared<ArrayBuffer>(GL_FLOAT, 3);
		m_pTangentBuffer->Generate();
		pVertexBuffer->SetArrayBuffer(TangentVisualizeVertexCode::ATTRIBUTE::TANGENT, m_pTangentBuffer);
		m_pRenderData = make_shared<RenderData>();
		m_pRenderData->SetGeometryData(PRIM_TYPE::PRIM_TYPE_POINTS, pVertexBuffer, pRenderData->GetIndexBuffer());
		m_pRenderData->SetShading(make_shared<TangentVisualizeShading>(vec4(0, 0, 0, 1), false));
	}

	m_pModel->CalcAlignOrientation();
	UpdateTangent(pModelNode, pPropertyArgs);


}
void ResolutionParameterProperty::UpdateTangent(IModelNode* pModelNode, ResolutionParameterPropertyArgs* pPropertyArgs)
{
	assert(m_pModel != nullptr);
	assert(m_pModel->GetAlignOrientation() != nullptr);

	std::vector<vec3> tangent;
	m_pModel->GetDownSampling()->GetData(pPropertyArgs->Level(), nullptr, nullptr, &tangent, nullptr);
	m_pTangentBuffer->Set(tangent);
}
}
}