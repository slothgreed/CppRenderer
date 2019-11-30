namespace KI
{
ModelNode::ModelNode(shared_ptr<IModel> model)
{
	m_name = "ModelNode";
	m_pModel = model;
	m_pModel->AddObserver(this);
	SetRenderData();
}

ModelNode::~ModelNode()
{
	m_pModel->RemoveObserver(this);
}

void ModelNode::Draw()
{
	m_pFaceMaterial->Draw();
	m_pEdgeMaterial->Draw();

	for (int i = 0; i < m_pProperty.size(); i++)
	{
		m_pProperty[i]->Draw();
	}

}

void ModelNode::ShowProperty()
{
	ImGui::Begin(m_name.data());
	ImGui::Text(m_bdb.ToString().data());
	ImGui::End();
}

void ModelNode::SetBDB(BDB bdb)
{
	m_bdb = bdb;

	m_pProperty.push_back(make_shared<BDBProperty>(m_bdb));
}

void ModelNode::VisibleNormal(bool visibility)
{
	if (m_pModel->HasVertexList())
	{
		vector<Vertex> vertexList;
		m_pModel->GetVertexList(vertexList);
		vector<vec3> normalList;
		for (int i = 0; i < vertexList.size(); i++)
		{
			normalList.push_back(vertexList[i].Position());
			normalList.push_back(vertexList[i].Position() + vertexList[i].Normal());
		}

		m_pProperty.push_back(make_shared<VectorProperty>(normalList, vec3(1, 0, 0)));
	}
	else
	{
		Logger::Output(LOG_LEVEL::DEBUG, "don't have vertex list");
	}
	//m_pProperty.push_back(make_shared<VectorProperty>());
}

void ModelNode::SetRenderData()
{
	if (m_pModel->HasVertexList() == false)
	{
		vector<vec3> facet;
		vector<vec3> normal;
		m_pModel->GetFacetList(facet, normal);
		auto pFaceBuffer = make_shared<DefaultVertexBuffer>();
		pFaceBuffer->Generate(VERTEX_LAYOUT_PN);
		pFaceBuffer->SetPosition(GL_TRIANGLES, facet);
		pFaceBuffer->SetNormal(normal);

		m_pFaceMaterial = make_shared<DefaultMaterial>();
		m_pFaceMaterial->SetVertexBuffer(pFaceBuffer);
		m_pFaceMaterial->CompileShader();

		vector<vec3> edge;
		m_pModel->GetEdgeList(edge);
		auto pEdgeBuffer = make_shared<DefaultVertexBuffer>();
		pEdgeBuffer->Generate(VERTEX_LAYOUT_P);
		pEdgeBuffer->SetPosition(GL_LINES, edge);

		m_pEdgeMaterial = make_shared<DefaultMaterial>();
		m_pEdgeMaterial->SetVertexBuffer(pEdgeBuffer);
		m_pEdgeMaterial->CompileShader();
	}
	else
	{
		vector<Vertex> vertex;
		vector<int> index;
		m_pModel->GetVertexList(vertex);
		m_pModel->GetFaceIndexList(index);
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

		m_pFaceMaterial = make_shared<DefaultMaterial>();
		m_pFaceMaterial->SetVertexBuffer(pFaceBuffer);
		m_pFaceMaterial->CompileShader();

		vector<vec3> edge;
		m_pModel->GetEdgeList(edge);
		auto pEdgeBuffer = make_shared<DefaultVertexBuffer>();
		pEdgeBuffer->Generate(VERTEX_LAYOUT_P);
		pEdgeBuffer->SetPosition(GL_LINES, edge);

		pEdgeBuffer->Generate(VERTEX_LAYOUT_P);
		pEdgeBuffer->SetPosition(GL_LINES, edge);

		m_pEdgeMaterial = make_shared<DefaultMaterial>();
		m_pEdgeMaterial->SetVertexBuffer(pEdgeBuffer);
		m_pEdgeMaterial->CompileShader();
	}

	BDB bdb;
	m_pModel->GetBDB(bdb);
	SetBDB(bdb);
	VisibleNormal(true);
}

void ModelNode::Update(void* sender, shared_ptr<EventArgs> args)
{
	SetRenderData();
}
}