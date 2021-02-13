namespace KI
{
namespace RenderModel
{
BVHProperty::BVHProperty()
{
}

BVHProperty::~BVHProperty()
{
}
void BVHProperty::BuildCore(IModelNode* pModelNode, IPropertyArgs* pPropertyArgs)
{
	auto pShading = make_shared<BasicShading>(vec4(0, 1, 0, 1));

	m_pVertexBuffer = make_shared<DefaultVertexBuffer>("BVH");
	auto pIndexBuffer = make_shared<IndexBuffer>();
	SetInstanceBuffer(pModelNode);
	SetBoxBuffer(m_pVertexBuffer, pIndexBuffer);
	m_pRenderData = make_shared<RenderData>();
	m_pRenderData->SetShading(pShading);
	m_pRenderData->SetGeometryData(PRIM_TYPE_POINTS, m_pVertexBuffer, pIndexBuffer);
	Update(pModelNode, pPropertyArgs);
}

void BVHProperty::Update(IModelNode* pModelNode, IPropertyArgs* pPropertyArgs)
{
	SetInstanceBuffer(pModelNode);
}

void BVHProperty::SetInstanceBuffer(IModelNode* pModelNode)
{
	vector<Vertex> vertexList;
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

	pModel->CalcBVH();

	PolygonModelNode* pPolygonModel = nullptr;
	if (IPolygonModel::IsPolygonModel(pModelNode->GetModel()->Type()))
	{
		pPolygonModel = (PolygonModelNode*)pModelNode;
	}
	else
	{
		assert(0);
		return;
	}
	
	std::vector<BDB> bdbs;
	pModel->GetBVH()->GetBVHBoundingBox(0, bdbs);
	m_pMatrixBuffer.resize(bdbs.size());
	for (int i = 0; i < bdbs.size(); i++) {
		m_pMatrixBuffer[i] = BDBUtility::GetModelMatrixFromMin(bdbs[i]);
	}
	m_pVertexBuffer->SetInstanceNum(bdbs.size());
	m_pVertexBuffer->SetInstanceMatrix(m_pMatrixBuffer);

}

void BVHProperty::SetBoxBuffer(shared_ptr<DefaultVertexBuffer> pVertexBuffer, shared_ptr<IndexBuffer> pIndexBuffer)
{
	assert(pVertexBuffer != nullptr);
	assert(pIndexBuffer != nullptr);

	Cube cube;
	cube.Build((CubeArgs(vec3(0), vec3(1), CubeArgs::PrimitiveType::LINES)));
	pVertexBuffer->SetPosition(cube.Position());

	assert(pIndexBuffer != nullptr);
	pIndexBuffer->Set(cube.Index());
}

void BVHProperty::Draw(shared_ptr<UniformStruct> pUniform)
{
	m_pRenderData->Draw(pUniform);
}
}
}

