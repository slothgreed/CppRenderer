namespace KI
{
namespace RenderModel
{
PolygonModelNode::PolygonModelNode(shared_ptr<IModel> model)
	: IRenderModelNode(model)
{
	m_name = "PolygonModelNode";
	SetRenderData();
}

PolygonModelNode::~PolygonModelNode()
{
}


void PolygonModelNode::ShowProperty()
{
	ImGui::Begin(m_name.data());
	ImGui::Text(m_bdb.ToString().data());
	ImGui::End();
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

shared_ptr<IVertexBuffer> PolygonModelNode::GetVertexBuffer()
{
	return GetRenderData(0)->GetVertexBuffer(); 
}

void PolygonModelNode::VisibleNormal(bool visibility)
{
	if (GetModel()->HasVertexList())
	{
		VisibleProperty(PROPERTY_TYPE::PROPERTY_TYPE_NORMAL, m_ui.visibleNormal);
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
		AddRenderData(0, pFaceData);

		vector<vec3> edge;
		GetModel()->GetEdgeList(edge);
		auto pEdgeBuffer = make_shared<DefaultVertexBuffer>();
		pEdgeBuffer->SetPosition(edge);

		auto pEdgeShading = make_shared<BasicShading>(vec4(0, 1, 0, 1));
		auto pEdgeData = make_shared <RenderData>(PRIM_TYPE_LINES, pEdgeBuffer);
		pEdgeData->SetShading(pEdgeShading);
		AddRenderData(1, pEdgeData);

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
		AddRenderData(0, pFaceData);

		vector<vec3> edge;
		GetModel()->GetEdgeList(edge);
		auto pEdgeBuffer = make_shared<DefaultVertexBuffer>();
		pEdgeBuffer->SetPosition(edge);

		auto pEdgeShading = make_shared<BasicShading>(vec4(0, 1, 0, 1));
		auto pEdgeData = make_shared <RenderData>(PRIM_TYPE_LINES, pEdgeBuffer);
		pEdgeData->SetShading(pEdgeShading);
		AddRenderData(1, pEdgeData);
	}

}

void PolygonModelNode::ShowUI()
{
	if (ImGui::Checkbox("Visible Mesh", &m_ui.visibleMesh)) {
		SetVisible(RENDER_DATA::MESH, m_ui.visibleMesh);
	}

	if (ImGui::Checkbox("Visible Edge", &m_ui.visibleEdge)) {
		SetVisible(RENDER_DATA::MESH, m_ui.visibleEdge);
	}

	if (ImGui::Checkbox("Visible BDB", &m_ui.visibleBDB)) {
		VisibleProperty(PROPERTY_TYPE::PROPERTY_TYPE_BDB, m_ui.visibleBDB);
	}

	if (ImGui::Checkbox("Visible Normal", &m_ui.visibleNormal)) {
		VisibleNormal(m_ui.visibleNormal);
	}
}

void PolygonModelNode::Update(void* sender, IEventArgs* args)
{
	SetRenderData();

	IModelNode::Update(sender, args);
}
}
}