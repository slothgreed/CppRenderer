RenderNode::RenderNode(std::shared_ptr<IShader> shader, std::shared_ptr<VertexBuffer> vertexBuffer)
{
	m_name = "RenderNode";
	m_pShader = shader;
	m_pVertexBuffer = vertexBuffer;
}

RenderNode::~RenderNode()
{
}

void RenderNode::Draw()
{
	m_pShader->Use();
	m_pVertexBuffer->Draw();
	for (int i = 0; i < m_pProperty.size(); i++)
	{
		m_pProperty[i]->Draw();
	}

	m_pShader->UnUse();
}

void RenderNode::ShowProperty()
{
	ImGui::Begin(m_name.data());
	ImGui::Text(m_bdb.ToString().data());
	ImGui::End();
}

void RenderNode::SetBDB(BDB bdb)
{
	m_bdb = bdb;
	m_pProperty.push_back(make_shared<BDBProperty>(m_bdb));
}

