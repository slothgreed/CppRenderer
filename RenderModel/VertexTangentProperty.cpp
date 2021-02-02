
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
	m_pShading = make_shared<TangentVisualizeShading>(vec4(0, 0, 0, 1), false);
	m_pShading->SetLength(1.0f);

	m_pRenderData = make_shared<RenderData>();
	m_pRenderData->SetShading(m_pShading);

	SetVBOData(pModelNode);

	InitializeUI();
}

void VertexTangentProperty::Update(IModelNode* pModelNode, IPropertyArgs* pPropertyArgs)
{
	SetVBOData(pModelNode);
}

void VertexTangentProperty::SetVBOData(IModelNode* pModelNode)
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
	
	if (m_pVertexBuffer == nullptr) {
		m_pVertexBuffer = make_shared<IVertexBuffer>("Tangent");
		m_pVertexBuffer->SetArrayBuffer(TangentVisualizeVertexCode::ATTRIBUTE::POSITION, pPolygonModel->GetVertexBuffer()->GetArrayBuffer(VERTEX_ATTRIB_POSITION));
		m_pVertexBuffer->SetArrayBuffer(TangentVisualizeVertexCode::ATTRIBUTE::NORMAL, pPolygonModel->GetVertexBuffer()->GetArrayBuffer(VERTEX_ATTRIB_NORMAL));
		m_pVertexBuffer->SetVertexSize(pModel->GetHalfEdgeDS()->VertexList().size());
		m_pTangentBuffer = make_shared<ArrayBuffer>(GL_FLOAT, 3);
		m_pTangentBuffer->Generate();
		m_pVertexBuffer->SetArrayBuffer(TangentVisualizeVertexCode::ATTRIBUTE::TANGENT, m_pTangentBuffer);
	}

	std::vector<vec3> tangents;
	tangents.resize(pModel->GetHalfEdgeDS()->VertexList().size());
	for (int i = 0; i < tangents.size(); i++) {
		tangents[i] = pModel->GetHalfEdgeDS()->VertexList()[i]->Tangent();
	}

	m_pTangentBuffer->Set(tangents);

	m_pRenderData->SetGeometryData(PRIM_TYPE_POINTS, m_pVertexBuffer);
}

void VertexTangentProperty::Draw(shared_ptr<UniformStruct> pUniform)
{
	m_pRenderData->Draw(pUniform);
}

void VertexTangentProperty::InitializeUI()
{
	m_ui.tangent.SetLabel("Length");
	m_ui.tangent.SetMin(0.0);
	m_ui.tangent.SetMax(1.0);
	m_ui.tangent.SetValue(0.5);

	m_ui.color[0] = 0;
	m_ui.color[1] = 0;
	m_ui.color[2] = 0;
}

void VertexTangentProperty::ShowUI()
{
	if (m_ui.tangent.Show()) {
		m_pShading->SetLength(m_ui.tangent.Value());
	}
}

}
}