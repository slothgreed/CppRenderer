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
	m_pFaceShader->Use();
	m_pFaceBuffer->Draw();
	m_pFaceShader->UnUse();

	m_pEdgeShader->Use();
	m_pEdgeBuffer->Draw();
	m_pEdgeShader->UnUse();

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
	vector<vec3> facet;
	vector<vec3> normal;
	m_pModel->GetFacetList(facet, normal);
	m_pFaceBuffer = make_shared<VertexBuffer>();
	m_pFaceBuffer->Generate(VERTEX_LAYOUT_PN);
	m_pFaceBuffer->SetPosition(GL_TRIANGLES, facet);
	m_pFaceBuffer->SetNormal(normal);

	ShaderBuildInfo facetShaderInfo;
	DefaultShader::GetVertexShaderDefine(VERTEX_LAYOUT::VERTEX_LAYOUT_PN, facetShaderInfo);
	m_pFaceShader = ShaderManager::Instance()->FindOrNew(facetShaderInfo);

	vector<vec3> edge;
	m_pModel->GetEdgeList(edge);
	m_pEdgeBuffer = make_shared<VertexBuffer>();
	m_pEdgeBuffer->Generate(VERTEX_LAYOUT_P);
	m_pEdgeBuffer->SetPosition(GL_LINES, edge);

	ShaderBuildInfo edgeShaderInfo;
	DefaultShader::GetVertexShaderDefine(VERTEX_LAYOUT::VERTEX_LAYOUT_PN, edgeShaderInfo);
	m_pEdgeShader = ShaderManager::Instance()->FindOrNew(edgeShaderInfo);

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