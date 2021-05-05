namespace KI
{
namespace RenderModel
{
PolygonModelNode::PolygonModelNode(shared_ptr<IModel> model)
	: IRenderModelNode(model)
{
	m_name = "PolygonModelNode";
	SetRenderData();
	InitializeUI();
}

PolygonModelNode::~PolygonModelNode()
{
}

IPolygonModel* PolygonModelNode::GetModel()
{
	if (IPolygonModel::IsPolygonModel(m_pModel->Type()))
	{
		return (IPolygonModel*)(m_pModel.get());
	}
	else
	{
		assert(0);
		return nullptr;
	}
}

shared_ptr<VertexBuffer> PolygonModelNode::GetVertexBuffer()
{
	return GetRenderData()->GetVertexBuffer(); 
}

void PolygonModelNode::VisibleNormal(bool visibility)
{
	if (GetModel()->HasVertexList())
	{
		VisibleProperty(PROPERTY_TYPE::PROPERTY_TYPE_NORMAL, visibility);
	}
	else
	{
		Logger::Output(LOG_LEVEL::LOG_LEVEL_DEBUG, "don't have vertex list");
	}
}

void PolygonModelNode::SetRenderData()
{
	if (GetModel()->HasVertexList() == false)
	{
		vector<vec3> facet;
		vector<vec3> normal;
		GetModel()->GetFacetList(facet, normal);
		auto pFaceBuffer = make_shared<DefaultVertexBuffer>();
		pFaceBuffer->SetPosition(facet);
		pFaceBuffer->SetNormal(normal);
		auto pFaceData = make_shared <RenderData>(PRIM_TYPE_TRIANGLES, pFaceBuffer);
		pFaceData->SetShading(make_shared<BasicShading>(vec4(0.7f, 0.7f, 0.7f, 1)));
		IModelNode::SetRenderData(pFaceData);

	}
	else
	{
		vector<Vertex> vertex;
		vector<int> index;
		GetModel()->GetVertexList(vertex);
		GetModel()->GetFaceIndexList(index);
		auto pFaceBuffer = make_shared<DefaultVertexBuffer>();

		vector<vec3> position;
		vector<vec3> normal;
		for (int i = 0; i < vertex.size(); i++)
		{
			position.push_back(vertex[i].Position());
			normal.push_back(vertex[i].Normal());
		}

		pFaceBuffer->SetPosition(position);
		pFaceBuffer->SetNormal(normal);
		
		auto pFaceIndex = make_shared <IndexBuffer>();
		pFaceIndex->Set(index);
		auto pFaceData = make_shared <RenderData>(PRIM_TYPE_TRIANGLES, pFaceBuffer, pFaceIndex);
		pFaceData->SetShading(make_shared<BasicShading>(vec4(0.7f, 0.7f, 0.7f, 1)));
		IModelNode::SetRenderData(pFaceData);
	}

}

void PolygonModelNode::InitializeUI()
{
	m_ui.meshVisibility.SetLabel("Mesh Visibility");
	m_ui.meshVisibility.SeValue(true);

	m_ui.meshColor.SetLabel("Mesh Color");
	m_ui.meshColor.SeValue(vec4(0.7f, 0.7f, 0.7f, 1.0f));

	m_ui.edgeVisibility.SetLabel("Edge Visibility");
	m_ui.edgeVisibility.SeValue(true);

	m_ui.edgeColor.SetLabel("Edge Color");
	m_ui.edgeColor.SeValue(vec4(0, 1, 0, 1));

	m_ui.normalVisibility.SetLabel("Normal Visibility");
	m_ui.normalVisibility.SeValue(true);

	m_ui.normalColor.SetLabel("Normal Color");
	m_ui.normalColor.SeValue(vec4(0.7f, 0.7f, 0.7f, 1.0f));

	m_ui.bdbVisibility.SetLabel("BDB Visibility");
	m_ui.bdbVisibility.SeValue(true);

	m_ui.bdbColor.SetLabel("BDB Color");
	m_ui.bdbColor.SeValue(vec4(0.0f));

}

void PolygonModelNode::ShowUI()
{
	if (m_ui.meshVisibility.Show()) {
		SetVisible(m_ui.meshVisibility.Value());
	}

	if (m_ui.edgeVisibility.Show()) {
		VisibleProperty(PROPERTY_TYPE::PROPERTY_TYPE_EDGE, m_ui.edgeVisibility.Value());
	}

	if (m_ui.bdbVisibility.Show()) {
		VisibleProperty(PROPERTY_TYPE::PROPERTY_TYPE_BDB, m_ui.bdbVisibility.Value());
	}

	if (m_ui.normalVisibility.Show()) {
		VisibleNormal(m_ui.normalVisibility.Value());
	}
}

void PolygonModelNode::Update(void* sender, IEventArgs* args)
{
	//SetRenderData();

	IModelNode::Update(sender, args);
}
}
}