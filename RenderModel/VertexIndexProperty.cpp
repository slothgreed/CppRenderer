
namespace KI
{
namespace RenderModel
{
VertexIndexProperty::VertexIndexProperty()
{
}

VertexIndexProperty::~VertexIndexProperty()
{

}

void VertexIndexProperty::BuildCore(IModelNode* pModelNode, IPropertyArgs* pPropertyArgs)
{
	VertexIndexPropertyArgs* pArgs = nullptr;
	if (pPropertyArgs && pPropertyArgs->Type() == PROPERTY_TYPE_VERTEX_INDEX)
	{
		pArgs = dynamic_cast<VertexIndexPropertyArgs*>(pPropertyArgs);
	}
	else
	{
		//assert(0);
		return;
	}

	SetIndexText(pModelNode, pArgs->Camera()->GetCamera());
}

void VertexIndexProperty::Update(IModelNode* pModelNode, IPropertyArgs* pPropertyArgs)
{
	VertexIndexPropertyArgs* pArgs = nullptr;
	if (pPropertyArgs->Type() == PROPERTY_TYPE_VERTEX_INDEX)
	{
		pArgs = dynamic_cast<VertexIndexPropertyArgs*>(pPropertyArgs);
	}
	else
	{
		assert(0);
		return;
	}

	SetIndexText(pModelNode, pArgs->Camera()->GetCamera());
}

void VertexIndexProperty::Update(void* sender, IEventArgs* pArgs)
{
	auto pCameraEvent = down_cast(CameraChangeEventArgs*, pArgs);
	if (pCameraEvent) {
		SetIndexText(ModelNode(), static_cast<ICamera*>(sender));
	}

}
void VertexIndexProperty::SetIndexText(IModelNode* pModelNode, const ICamera* pCamera)
{
	assert(pCamera != nullptr);
	assert(pModelNode != nullptr);

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

	mat4x4 matrix = pCamera->Projection()* pCamera->ViewMatrix() * pModelNode->GetModelMatrix();
	if (m_indexText.size() == 0) {
		m_indexText.resize(pModel->GetHalfEdgeDS()->VertexList().size());
		m_pRenderDatas.resize(m_indexText.size());
		auto pShading = make_shared<BasicShading>(BASIC_SHADING_TYPE_TEXTURE);
		pShading->SetTexture(m_indexText[0].GetTexture());
		for (int i = 0; i < m_indexText.size(); i++) {
			auto pVertexBuffer = make_shared<DefaultVertexBuffer>();
			auto pIndexBuffer = make_shared<IndexBuffer>();
			auto pVertex = pModel->GetHalfEdgeDS()->VertexList()[i];
			vec3 screenPos = MathHelper::WorldToScreenPos(pCamera->Projection(), pCamera->ViewMatrix(), pModelNode->GetModelMatrix(), pVertex->Position());
			m_indexText[i].Build(HUDTextArgs(std::to_string(pVertex->Index()), screenPos.x, screenPos.y));
			m_pRenderDatas[i] = make_shared<RenderData>();
			m_pRenderDatas[i]->SetShading(pShading);
			pVertexBuffer->SetPosition(m_indexText[i].Position());
			pVertexBuffer->SetTexcoord(m_indexText[i].Texcoord());
			pIndexBuffer->Set(m_indexText[i].Index());
			m_pRenderDatas[i]->SetGeometryData(PRIM_TYPE::PRIM_TYPE_TRIANGLES, pVertexBuffer, pIndexBuffer);
		}
	}
	else
	{
		for (int i = 0; i < m_indexText.size(); i++) {
			auto pVertex = pModel->GetHalfEdgeDS()->VertexList()[i];
			vec3 screenPos = MathHelper::WorldToScreenPos(pCamera->Projection(), pCamera->ViewMatrix(), pModelNode->GetModelMatrix(), pVertex->Position());
			m_indexText[i].SetWindowPosition(screenPos.x, screenPos.y);
		}
	}
}

void VertexIndexProperty::Draw(shared_ptr<UniformStruct> pUniform)
{
	for (int i = 0; i < m_pRenderDatas.size(); i++)
	{
		m_pRenderDatas[i]->Draw(pUniform);
	}
}

}
}