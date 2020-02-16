namespace KI
{
ModelNode::ModelNode(shared_ptr<IModel> model)
{
	m_name = "ModelNode";
	m_pModel = model;
	m_pModel->AddObserver(this);
	VisibleBDB(true);
	VisibleNormal(true);
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

	DrawProperty();

}

void ModelNode::ShowProperty()
{
	ImGui::Begin(m_name.data());
	ImGui::Text(m_bdb.ToString().data());
	ImGui::End();
}

void ModelNode::VisibleBDB(bool visibility)
{
	m_pModel->GetBDB(m_bdb);
	AddProperty(make_shared<BDBProperty>());
}

void ModelNode::VisibleNormal(bool visibility)
{
	if (m_pModel->HasVertexList())
	{
		AddProperty(make_shared<NormalProperty>());
	}
	else
	{
		Logger::Output(LOG_LEVEL::DEBUG, "don't have vertex list");
	}
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

		m_pEdgeMaterial = make_shared<DefaultMaterial>();
		m_pEdgeMaterial->SetVertexBuffer(pEdgeBuffer);
		m_pEdgeMaterial->CompileShader();
	}

}

void ModelNode::Update(void* sender, shared_ptr<EventArgs> args)
{
	SetRenderData();

	IModelNode::Update(sender, args);
}
}