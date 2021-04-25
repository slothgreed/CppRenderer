
namespace KI
{
namespace RenderModel
{
QuadPositionProperty::QuadPositionProperty()
{
}

QuadPositionProperty::~QuadPositionProperty()
{

}

void QuadPositionProperty::BuildCore(IModelNode* pModelNode, IPropertyArgs* pPropertyArgs)
{
	m_pShading = make_shared<BasicShading>(vec4(1, 0, 0, 1));

	m_pRenderData = make_shared<RenderData>();
	m_pRenderData->SetShading(m_pShading);

	SetVBOData(pModelNode);
}

void QuadPositionProperty::Update(IModelNode* pModelNode, IPropertyArgs* pPropertyArgs)
{
	SetVBOData(pModelNode);
}

void QuadPositionProperty::SetVBOData(IModelNode* pModelNode)
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
	
	if (m_pVertexBuffer == nullptr) {
		m_pVertexBuffer = make_shared<DefaultVertexBuffer>("Position");
		std::vector<Vertex> vertexList;
		std::vector<vec3> quadList;
		for (int i = 0; i < pModel->GetHalfEdgeDS()->VertexList().size(); i++)
		{
			quadList.push_back(pModel->GetHalfEdgeDS()->VertexList()[i]->QuadPosition());
		}
		m_pVertexBuffer->SetPosition(quadList);
	}

	m_pRenderData->SetGeometryData(PRIM_TYPE_POINTS, m_pVertexBuffer);
}

void QuadPositionProperty::Draw(shared_ptr<UniformStruct> pUniform)
{
	glPointSize(5);
	m_pRenderData->Draw(pUniform);
}

void QuadPositionProperty::InitializeUI()
{
}

void QuadPositionProperty::ShowUI()
{
}

}
}