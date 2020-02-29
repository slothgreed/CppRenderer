namespace KI
{
PolygonModelNode::PolygonModelNode(shared_ptr<IModel> model)
	: IModelNode(model)
{
	m_name = "PolygonModelNode";
	VisibleBDB(true);
	VisibleNormal(true);
	SetRenderData();
}

PolygonModelNode::~PolygonModelNode()
{
}

void PolygonModelNode::Draw()
{
	m_pFaceMaterial->Draw(m_pFaceBuffer.get());
	m_pEdgeMaterial->Draw(m_pEdgeBuffer.get());

	DrawProperty();

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
		pFaceBuffer->Generate(VERTEX_LAYOUT_PN);
		pFaceBuffer->SetPosition(GL_TRIANGLES, facet);
		pFaceBuffer->SetNormal(normal);


		vector<vec3> edge;
		GetModel()->GetEdgeList(edge);
		auto pEdgeBuffer = make_shared<DefaultVertexBuffer>();
		pEdgeBuffer->Generate(VERTEX_LAYOUT_P);
		pEdgeBuffer->SetPosition(GL_LINES, edge);

		m_pFaceMaterial = make_shared<DefaultMaterial>();
		m_pEdgeMaterial = make_shared<DefaultMaterial>();

		m_pFaceBuffer = pFaceBuffer;
		m_pEdgeBuffer = pEdgeBuffer;
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

		pFaceBuffer->Generate(VERTEX_LAYOUT_PN);
		pFaceBuffer->SetPosition(GL_TRIANGLES, position);
		pFaceBuffer->SetNormal(normal);
		pFaceBuffer->SetIndex(index);


		vector<vec3> edge;
		GetModel()->GetEdgeList(edge);
		auto pEdgeBuffer = make_shared<DefaultVertexBuffer>();
		pEdgeBuffer->Generate(VERTEX_LAYOUT_P);
		pEdgeBuffer->SetPosition(GL_LINES, edge);

		m_pFaceMaterial = make_shared<DefaultMaterial>();
		m_pEdgeMaterial = make_shared<DefaultMaterial>();

		m_pFaceBuffer = pFaceBuffer;
		m_pEdgeBuffer = pEdgeBuffer;
	}

}

void PolygonModelNode::Pick(const vec3& direction, PickResult& distance)
{

}

void PolygonModelNode::Update(void* sender, IEventArgs* args)
{
	SetRenderData();

	IModelNode::Update(sender, args);
}
}