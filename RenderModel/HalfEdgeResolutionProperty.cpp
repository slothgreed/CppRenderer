namespace KI
{
namespace RenderModel
{
HalfEdgeResolutionPropertyArgs& HalfEdgeResolutionProperty::DefaultArgs()
{
	static HalfEdgeResolutionPropertyArgs defaultArgs(0);

	return defaultArgs;
}
HalfEdgeResolutionProperty::HalfEdgeResolutionProperty()
{
}

void HalfEdgeResolutionProperty::BuildCore(IModelNode* pModelNode, IPropertyArgs* pPropertyArgs)
{
	assert(pModelNode != nullptr);
	auto pRenderData = pModelNode->GetRenderData(0);
	auto pMeshBuffer = pRenderData->GetVertexBuffer();
	m_pRenderData = make_shared<RenderData>();
	SetModel(pModelNode);
	m_colorMap.resize(pMeshBuffer->GetVertexSize());
	for (int i = 0; i < m_colorMap.size(); i++) {
		m_colorMap[i].x = Gaccho::rnd(0, 255) / 255.0f;
		m_colorMap[i].y = Gaccho::rnd(0, 255) / 255.0f;
		m_colorMap[i].z = Gaccho::rnd(0, 255) / 255.0f;
	}

	m_pModel->CalcDownSampling();

	vector<vec3> colors;
	GetClusterColor(pPropertyArgs, colors);

	
	auto pVertexBuffer = make_shared<DefaultVertexBuffer>();
	pVertexBuffer->SetArrayBuffer(VERTEX_ATTRIB::VERTEX_ATTRIB_POSITION, pMeshBuffer->GetArrayBuffer(VERTEX_ATTRIB::VERTEX_ATTRIB_POSITION));
	pVertexBuffer->SetVertexSize(pMeshBuffer->GetVertexSize());
	pVertexBuffer->SetColor(colors);
	m_pRenderData->SetGeometryData(PRIM_TYPE_TRIANGLES, pVertexBuffer, pRenderData->GetIndexBuffer());

	m_pRenderData->SetShading(make_shared<VertexShading>(VERTEX_SHADING_COLOR));
}

void HalfEdgeResolutionProperty::Update(IModelNode* pModelNode, IPropertyArgs* pPropertyArgs)
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

void HalfEdgeResolutionProperty::SetModel(IModelNode* pModelNode)
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
void HalfEdgeResolutionProperty::GetClusterColor(IPropertyArgs* pPropertyArgs, vector<vec3>& colors)
{
	auto pArgs = dynamic_cast<HalfEdgeResolutionPropertyArgs*>(pPropertyArgs);
	if (pArgs == nullptr)
	{
		pArgs = &DefaultArgs();
	}

	auto pDownSampling = m_pModel->GetDownSampling();
	if (pDownSampling == nullptr)
	{
		assert(0);
		return;
	}


	vector<int> clusterIndex;
	pDownSampling->GetCluster(pArgs->m_level, clusterIndex);
	int maxIndex = *std::max_element(clusterIndex.begin(), clusterIndex.end());
	colors.resize(clusterIndex.size());

	for (int i = 0; i < colors.size(); i++) {
		colors[i] = m_colorMap[clusterIndex[i]];
	}
}
void HalfEdgeResolutionProperty::Draw(shared_ptr<UniformStruct> pUniform)
{
	m_pRenderData->Draw(pUniform);
}

void HalfEdgeResolutionProperty::InitializeUI()
{
	m_ui.resolution.SetLabel("Level");
	m_ui.resolution.SetMin(0);
	m_ui.resolution.SetValue(0);
	m_ui.resolution.SetMax(m_pModel->GetDownSampling()->GetResolutionNum() - 1);

}
void HalfEdgeResolutionProperty::ShowUI()
{
	if (m_ui.resolution.Show()) {
		Update(nullptr, &HalfEdgeResolutionPropertyArgs(m_ui.resolution.Value()));
	}
}
}
}