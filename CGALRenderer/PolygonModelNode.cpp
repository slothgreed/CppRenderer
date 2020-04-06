namespace KI
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

void PolygonModelNode::Draw()
{
	if (m_pFaceMaterial != NULL && m_pFaceBuffer != NULL)
	{
		m_pFaceMaterial->Draw(m_pFaceBuffer.get(), m_pFaceIndex.get());
	}

	if (m_pEdgeMaterial != NULL && m_pEdgeBuffer != NULL)
	{
		m_pEdgeMaterial->Draw(m_pEdgeBuffer.get());
	}

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
		pFaceBuffer->SetPosition(GL_TRIANGLES, facet);
		pFaceBuffer->SetNormal(normal);
		m_pFaceBuffer = pFaceBuffer;
		m_pFaceMaterial = make_shared<DefaultMaterial>();

		vector<vec3> edge;
		GetModel()->GetEdgeList(edge);
		auto pEdgeBuffer = make_shared<DefaultVertexBuffer>();
		pEdgeBuffer->SetPosition(GL_LINES, edge);

		m_pEdgeMaterial = make_shared<DefaultMaterial>();
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

		pFaceBuffer->SetPosition(GL_TRIANGLES, position);
		pFaceBuffer->SetNormal(normal);
		m_pFaceMaterial = make_shared<DefaultMaterial>();
		m_pFaceBuffer = pFaceBuffer;
		m_pFaceIndex = make_shared <IndexBuffer>();
		m_pFaceIndex->Set(GL_TRIANGLES, index);

		vector<vec3> edge;
		GetModel()->GetEdgeList(edge);
		auto pEdgeBuffer = make_shared<DefaultVertexBuffer>();
		pEdgeBuffer->SetPosition(GL_LINES, edge);

		auto pEdgeMaterial = make_shared<DefaultMaterial>();
		pEdgeMaterial->SetFixColor(vec4(0));
		m_pEdgeMaterial = pEdgeMaterial;
		m_pEdgeBuffer = pEdgeBuffer;
	}

}

void PolygonModelNode::VisibleFace(bool visibility)
{

}

void PolygonModelNode::VisibleEdge(bool visibility)
{

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