namespace KI
{
PrimitiveNode::PrimitiveNode(shared_ptr<IShader> shader, shared_ptr<DefaultVertexBuffer> buffer)
{
	m_name = "Primitive";

	if (buffer->PrimitiveType() == GL_LINES)
	{
		auto lineMaterial = make_shared<LineMaterial>();
		lineMaterial->SetLineWidth(5);
		m_pMaterial = lineMaterial;
	}
	else if(buffer->PrimitiveType() == GL_POINTS)
	{
		auto pointMaterial = make_shared<PointMaterial>();
		pointMaterial->SetPointSize(5);
		m_pMaterial = pointMaterial;
	}
	else
	{
		m_pMaterial = make_shared<DefaultMaterial>();
	}

	m_pMaterial->SetVertexBuffer(buffer);
	m_pMaterial->CompileShader();
}

PrimitiveNode::~PrimitiveNode()
{
}

void PrimitiveNode::Draw()
{
	m_pMaterial->Draw();

	Logger::GLError();
}


void PrimitiveNode::Update(void* sender, shared_ptr<EventArgs> args)
{

}

void PrimitiveNode::ShowProperty()
{

}
}
