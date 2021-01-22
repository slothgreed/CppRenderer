namespace KI
{
namespace RenderModel
{
HalfEdgeResolutionProperty::HalfEdgeResolutionProperty()
{
}

void HalfEdgeResolutionProperty::Build(IModelNode* pModelNode, IPropertyArgs* pPropertyArgs)
{
	auto pRenderData = pModelNode->GetRenderData(0);
	auto pMeshBuffer = pRenderData->GetVertexBuffer();
	m_pRenderData = make_shared<RenderData>();

	m_colorMap.resize(pMeshBuffer->GetVertexSize());
	for (int i = 0; i < m_colorMap.size(); i++) {
		m_colorMap[i].x = Gaccho::rnd(0, 255) / 255.0;
		m_colorMap[i].y = Gaccho::rnd(0, 255) / 255.0;
		m_colorMap[i].z = Gaccho::rnd(0, 255) / 255.0;
	}

	vector<vec3> colors;
	GetClusterColor(pModelNode, pPropertyArgs, colors);



	auto pVertexBuffer = make_shared<DefaultVertexBuffer>();
	pVertexBuffer->SetArrayBuffer(VERTEX_ATTRIB::VERTEX_ATTRIB_POSITION, pMeshBuffer->GetArrayBuffer(VERTEX_ATTRIB::VERTEX_ATTRIB_POSITION));
	pVertexBuffer->SetVertexSize(pMeshBuffer->GetVertexSize());
	pVertexBuffer->SetColor(colors);
	//m_pRenderData->SetGeometryData(PRIM_TYPE_POINTS, pVertexBuffer);
	m_pRenderData->SetGeometryData(PRIM_TYPE_TRIANGLES, pVertexBuffer, pRenderData->GetIndexBuffer());

	m_pRenderData->SetShading(make_shared<VertexShading>(VERTEX_SHADING_COLOR));

}

void HalfEdgeResolutionProperty::Update(IModelNode* pModelNode, IPropertyArgs* pPropertyArgs)
{
	vector<vec3> colors;
	GetClusterColor(pModelNode, pPropertyArgs, colors);

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

void HalfEdgeResolutionProperty::GetClusterColor(IModelNode* pModelNode, IPropertyArgs* pPropertyArgs, vector<vec3>& colors)
{
	shared_ptr<HalfEdgeModel> pModel;
	if (pModelNode->GetModel()->Type() == MODEL_TYPE_HALF_EDGE)
	{
		pModel = static_pointer_cast<HalfEdgeModel>(pModelNode->GetModel());
	}
	else
	{
		assert(0);
		return;
	}

	auto pArgs = dynamic_cast<HalfEdgeResolutionPropertyArgs*>(pPropertyArgs);
	if (pArgs == nullptr)
	{
		assert(0);
		return;
	}

	auto pDownSampling = pModel->GetDownSampling();
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

}
}