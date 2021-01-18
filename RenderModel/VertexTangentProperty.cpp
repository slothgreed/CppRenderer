
namespace KI
{
namespace RenderModel
{
VertexTangentProperty::VertexTangentProperty()
{
}

VertexTangentProperty::~VertexTangentProperty()
{

}

void VertexTangentProperty::Build(IModelNode* pModelNode, IPropertyArgs* pPropertyArgs)
{
	m_pShading = make_shared<TangentVisualizeShading>(vec4(0), true);
	m_pShading->SetLength(5.0f);

	m_pRenderData = make_shared<RenderData>();
	m_pRenderData->SetShading(m_pShading);

	SetVBOData(pModelNode);
}

void VertexTangentProperty::Update(IModelNode* pModelNode, IPropertyArgs* pPropertyArgs)
{
	SetVBOData(pModelNode);
}

void VertexTangentProperty::SetVBOData(IModelNode* pModelNode)
{
	vector<Vertex> vertexList;
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

	m_pRenderData->SetGeometryData(PRIM_TYPE_POINTS, pVertexBuffer);
}

void VertexTangentProperty::Draw(shared_ptr<UniformStruct> pUniform)
{
	m_pRenderData->Draw(pUniform);
}

}
}