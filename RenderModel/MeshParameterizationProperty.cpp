
namespace KI
{
namespace RenderModel
{
MeshParameterizationProperty::MeshParameterizationProperty()
{
}

MeshParameterizationProperty::~MeshParameterizationProperty()
{

}

void MeshParameterizationProperty::BuildCore(IModelNode* pModelNode, IPropertyArgs* pPropertyArgs)
{
	m_pRenderData = make_shared<RenderData>();
	m_pRenderData->SetShading(make_shared<MeshParameterizationShading>());
	Update(pModelNode, pPropertyArgs);
}

void MeshParameterizationProperty::Update(IModelNode* pModelNode, IPropertyArgs* pPropertyArgs)
{
	MeshParameterizationPropertyArgs* pArgs = &MeshParameterizationPropertyArgs();
	if (pPropertyArgs && pPropertyArgs->Type() == PROPERTY_TYPE_MESH_PARAMETERIZATION)
	{
		pArgs = down_cast(MeshParameterizationPropertyArgs*, pPropertyArgs);
	}

	BuildVBO(pModelNode, pArgs);
}

void MeshParameterizationProperty::Update(void* sender, IEventArgs* pArgs)
{

}
void MeshParameterizationProperty::BuildVBO(IModelNode* pModelNode, MeshParameterizationPropertyArgs* pPropertyArgs)
{
	vector<Vertex> vertexList;
	shared_ptr<HalfEdgeModel> pModel = static_pointer_cast<HalfEdgeModel>(pModelNode->GetModel());
	if (m_pVertexBuffer == nullptr) {
		m_ArrayBuffers.positionBuffer = make_shared<ArrayBuffer>(GL_FLOAT, 3);
		m_ArrayBuffers.normalBuffer = make_shared<ArrayBuffer>(GL_FLOAT, 3);
		m_ArrayBuffers.tangentBuffer = make_shared<ArrayBuffer>(GL_FLOAT, 3);
		m_ArrayBuffers.uvBuffer = make_shared<ArrayBuffer>(GL_FLOAT, 3);
		m_ArrayBuffers.tangentBuffer->Generate();
		m_ArrayBuffers.positionBuffer->Generate();
		m_ArrayBuffers.normalBuffer->Generate();
		m_ArrayBuffers.uvBuffer->Generate();

		m_pVertexBuffer = make_shared<IVertexBuffer>("Mesh Parameterization");
	}
	std::vector<vec3> position;
	std::vector<vec3> normal;
	std::vector<vec3> tangent;
	std::vector<vec3> uv;

	pModel->GetDownSampling()->GetData(pPropertyArgs->Level(), &position, &normal, &tangent, &uv);

	m_pVertexBuffer->SetArrayBuffer(MeshParameterizationVertCode::ATTRIBUTE::POSITION, m_ArrayBuffers.positionBuffer);
	m_pVertexBuffer->SetArrayBuffer(MeshParameterizationVertCode::ATTRIBUTE::NORMAL, m_ArrayBuffers.normalBuffer);
	m_pVertexBuffer->SetArrayBuffer(MeshParameterizationVertCode::ATTRIBUTE::TANGENT, m_ArrayBuffers.tangentBuffer);
	m_pVertexBuffer->SetArrayBuffer(MeshParameterizationVertCode::ATTRIBUTE::UV, m_ArrayBuffers.uvBuffer);
	m_pVertexBuffer->SetVertexSize(position.size());


	m_ArrayBuffers.positionBuffer->Set(position);
	m_ArrayBuffers.normalBuffer->Set(normal);
	m_ArrayBuffers.tangentBuffer->Set(tangent);
	m_ArrayBuffers.uvBuffer->Set(uv);

	m_pRenderData->SetGeometryData(PRIM_TYPE_TRIANGLES, m_pVertexBuffer);
	m_pRenderData->SetIndexBuffer(PRIM_TYPE_TRIANGLES, pModelNode->GetRenderData(0)->GetIndexBuffer());
}

void MeshParameterizationProperty::Draw(shared_ptr<UniformStruct> pUniform)
{
	m_pRenderData->Draw(pUniform);
}

}
}