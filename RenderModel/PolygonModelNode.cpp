namespace KI
{
namespace RenderModel
{
PolygonModelNode::PolygonModelNode(shared_ptr<IModel> model)
	: IModelNode(model)
{
	m_name = "PolygonModelNode";
	SetRenderData();
	VisibleBDB(true);
	VisibleNormal(true);
}

PolygonModelNode::~PolygonModelNode()
{
}

void PolygonModelNode::DrawCore(shared_ptr<UniformStruct> pUniform)
{
	if (m_pFaceData != NULL)
	{
		m_pFaceData->Draw(pUniform);
	}

	if (m_pEdgeData != NULL)
	{
		m_pEdgeData->Draw(pUniform);
	}

	DrawProperty(pUniform);

}

void PolygonModelNode::ShowProperty()
{
	//ImGui::Begin(m_name.data());
	//ImGui::Text(m_bdb.ToString().data());
	//ImGui::End();
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

void PolygonModelNode::VisibleBDB(bool visibility)
{
	GetModel()->GetBDB(m_bdb);
	AddProperty(make_shared<BDBProperty>());
}

shared_ptr<IVertexBuffer> PolygonModelNode::GetVertexBuffer()
{
	if (m_pFaceData == nullptr)
	{
		assert(0);
		return nullptr;
	}

	return m_pFaceData->GetVertexBuffer(); 
}

void PolygonModelNode::VisibleNormal(bool visibility)
{
	if (GetModel()->HasVertexList())
	{
		AddProperty(make_shared<NormalProperty>());
	}
	else
	{
		Logger::Output(LOG_LEVEL::DEBUG, "don't have vertex list");
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
		m_pFaceData = make_shared <RenderData>(PRIM_TYPE_TRIANGLES, pFaceBuffer);
		m_pFaceData->SetShading(make_shared<BasicShading>(vec4(0.7f, 0.7f, 0.7f, 1)));

		vector<vec3> edge;
		GetModel()->GetEdgeList(edge);
		auto pEdgeBuffer = make_shared<DefaultVertexBuffer>();
		pEdgeBuffer->SetPosition(edge);

		auto pEdgeShading = make_shared<BasicShading>(vec4(0, 1, 0, 1));
		m_pEdgeData = make_shared <RenderData>(PRIM_TYPE_LINES, pEdgeBuffer);
		m_pEdgeData->SetShading(pEdgeShading);
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
		m_pFaceData = make_shared <RenderData>(PRIM_TYPE_TRIANGLES, pFaceBuffer, pFaceIndex);
		m_pFaceData->SetShading(make_shared<BasicShading>(vec4(0.7f, 0.7f, 0.7f, 1)));

		vector<vec3> edge;
		GetModel()->GetEdgeList(edge);
		auto pEdgeBuffer = make_shared<DefaultVertexBuffer>();
		pEdgeBuffer->SetPosition(edge);

		auto pEdgeShading = make_shared<BasicShading>(vec4(0, 1, 0, 1));
		m_pEdgeData = make_shared <RenderData>(PRIM_TYPE_LINES, pEdgeBuffer);
		m_pEdgeData->SetShading(pEdgeShading);
	}

}

void PolygonModelNode::VisibleFace(bool visibility)
{

}

void PolygonModelNode::VisibleEdge(bool visibility)
{

}

void PolygonModelNode::AddPartSelect(TOPOLOGY_TYPE type, int first, int count)
{
	auto pShading = ShadingManager::Instance()->GetSystemShading(SYSTEM_SHADING::SYSTEM_SHADING_SELECTION);
	if (type == TOPOLOGY_TYPE::TOPOLOGY_TYPE_FACE)
	{
		if (m_pFaceData->HasRenderRegion())
		{
			m_pFaceData->ClearRenderRegion();
		}

		m_pFaceData->AddRenderRegion("Selection", pShading, first, count);
	}
	else
	{
		assert(0);
	}
}

void PolygonModelNode::Update(void* sender, IEventArgs* args)
{
	SetRenderData();

	IModelNode::Update(sender, args);
}
}
}