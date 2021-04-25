
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

void VertexTangentProperty::BuildCore(IModelNode* pModelNode, IPropertyArgs* pPropertyArgs)
{
	m_pShading = make_shared<TangentVisualizeShading>(vec4(0, 0, 0, 1), false);
	m_pShading->SetLength(1.0f);
	m_pShading->SetOffset(0.1);

	m_pRenderData = make_shared<RenderData>();
	m_pRenderData->SetShading(m_pShading);

	Update(pModelNode, pPropertyArgs);
}

void VertexTangentProperty::Update(IModelNode* pModelNode, IPropertyArgs* pPropertyArgs)
{
	if (pPropertyArgs == nullptr) {
		SetVBOData(pModelNode, &VertexTangentPropertyArgs(0));
	}
	else if (pPropertyArgs->Type() == PROPERTY_TYPE_VERTEX_TANGENT) {
		SetVBOData(pModelNode, static_cast<VertexTangentPropertyArgs*>(pPropertyArgs));
	}
}

shared_ptr<HalfEdgeModel> VertexTangentProperty::GetHalfEdgeModel()
{
	if (ModelNode()->GetModel()->Type() == MODEL_TYPE_HALF_EDGE)
	{
		return static_pointer_cast<HalfEdgeModel>(ModelNode()->GetModel());
	}
	else
	{
		assert(0);
		return nullptr;
	}
}

void VertexTangentProperty::SetVBOData(IModelNode* pModelNode, VertexTangentPropertyArgs* pPropertyArgs)
{
	
	vector<Vertex> vertexList;
	shared_ptr<HalfEdgeModel> pModel = GetHalfEdgeModel();
	if (m_pVertexBuffer == nullptr) {
		m_ArrayBuffers.tangentBuffer = make_shared<ArrayBuffer>(GL_FLOAT, 3);
		m_ArrayBuffers.positionBuffer = make_shared<ArrayBuffer>(GL_FLOAT, 3);
		m_ArrayBuffers.normalBuffer = make_shared<ArrayBuffer>(GL_FLOAT, 3);

		m_ArrayBuffers.tangentBuffer->Generate();
		m_ArrayBuffers.positionBuffer->Generate();
		m_ArrayBuffers.normalBuffer->Generate();

		m_pVertexBuffer = make_shared<IVertexBuffer>("Tangent");
	}
	std::vector<vec3> position;
	std::vector<vec3> normal;
	std::vector<vec3> tangent;

	pModel->GetDownSampling()->GetData(pPropertyArgs->Level(), &position, &normal, &tangent);

	m_pVertexBuffer->SetArrayBuffer(TangentVisualizeVertexCode::ATTRIBUTE::POSITION, m_ArrayBuffers.positionBuffer);
	m_pVertexBuffer->SetArrayBuffer(TangentVisualizeVertexCode::ATTRIBUTE::NORMAL, m_ArrayBuffers.normalBuffer);
	m_pVertexBuffer->SetArrayBuffer(TangentVisualizeVertexCode::ATTRIBUTE::TANGENT, m_ArrayBuffers.tangentBuffer);
	m_pVertexBuffer->SetVertexSize(position.size());

	
	m_ArrayBuffers.positionBuffer->Set(position);
	m_ArrayBuffers.normalBuffer->Set(normal);
	m_ArrayBuffers.tangentBuffer->Set(tangent);

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

	m_ui.offset.SetLabel("Offset Normal");
	m_ui.offset.SetMin(0.0);
	m_ui.offset.SetMax(1.0);
	m_ui.offset.SetValue(0.1f);

	m_ui.level.SetLabel("Tangent Level");
	m_ui.level.SetMin(0);
	m_ui.level.SetMax(GetHalfEdgeModel()->GetDownSampling()->GetResolutionNum() - 1);
	m_ui.level.SetValue(0);
}

void VertexTangentProperty::ShowUI()
{
	if (m_ui.tangent.Show()) {
		m_pShading->SetLength(m_ui.tangent.Value());
	}

	if (m_ui.offset.Show()) {
		m_pShading->SetOffset(m_ui.offset.Value());
	}

	if (m_ui.level.Show()) {
		SetVBOData(ModelNode(), &VertexTangentPropertyArgs(m_ui.level.Value()));
	}

}

}
}