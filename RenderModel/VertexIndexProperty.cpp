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
	m_indexText.resize(pModel->GetHalfEdgeDS()->VertexList().size());
	for (int i = 0; i < m_indexText.size(); i++) {
		auto pVertex = pModel->GetHalfEdgeDS()->VertexList()[i];
		vec3 screenPos = MathHelper::WorldToScreenPos(pCamera->Projection(), pCamera->ViewMatrix(), pModelNode->GetModelMatrix(), pVertex->Position());
		m_indexText[i].SetPosition(screenPos);
		m_indexText[i].SetValue(std::to_string(pVertex->Index()));
	}
}

void VertexIndexProperty::Draw(shared_ptr<UniformStruct> pUniform)
{
	for (int i = 0; i < m_indexText.size(); i++)
	{
		m_indexText[i].ShowUI();
	}
}

}
}