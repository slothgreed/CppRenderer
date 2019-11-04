RenderNode::RenderNode(std::shared_ptr<Shader> shader, std::shared_ptr<VertexBuffer> vertexBuffer)
{
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
	m_pShader->UnUse();
}