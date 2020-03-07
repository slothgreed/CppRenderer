namespace KI
{
ManipulatorNode::ManipulatorNode()
{
	SetRenderData();
}

ManipulatorNode::~ManipulatorNode()
{
	delete m_pFaceBuffers[MANIPULATOR_HANDLE_X];
	delete m_pFaceBuffers[MANIPULATOR_HANDLE_Y];
	delete m_pFaceBuffers[MANIPULATOR_HANDLE_Z];

	delete m_pEdgeBuffers[MANIPULATOR_HANDLE_X];
	delete m_pEdgeBuffers[MANIPULATOR_HANDLE_Y];
	delete m_pEdgeBuffers[MANIPULATOR_HANDLE_Z];

	delete m_pMaterial;
}

void ManipulatorNode::ShowProperty()
{
	//assert(0);
}

void ManipulatorNode::SetRenderData()
{
	manipulator.Build();
	m_pFaceBuffers[MANIPULATOR_HANDLE_X] = new DefaultVertexBuffer();
	m_pFaceBuffers[MANIPULATOR_HANDLE_Y] = new DefaultVertexBuffer();
	m_pFaceBuffers[MANIPULATOR_HANDLE_Z] = new DefaultVertexBuffer();

	m_pEdgeBuffers[MANIPULATOR_HANDLE_X] = new DefaultVertexBuffer();
	m_pEdgeBuffers[MANIPULATOR_HANDLE_Y] = new DefaultVertexBuffer();
	m_pEdgeBuffers[MANIPULATOR_HANDLE_Z] = new DefaultVertexBuffer();
	
	GenManipulatorHandleVBO(
		m_pFaceBuffers[MANIPULATOR_HANDLE_X],
		m_pEdgeBuffers[MANIPULATOR_HANDLE_X],
		MANIPULATOR_HANDLE::MANIPULATOR_HANDLE_X);
	GenManipulatorHandleVBO(
		m_pFaceBuffers[MANIPULATOR_HANDLE_Y],
		m_pEdgeBuffers[MANIPULATOR_HANDLE_Y],
		MANIPULATOR_HANDLE::MANIPULATOR_HANDLE_Y);

	GenManipulatorHandleVBO(
		m_pFaceBuffers[MANIPULATOR_HANDLE_Z],
		m_pEdgeBuffers[MANIPULATOR_HANDLE_Z],
		MANIPULATOR_HANDLE::MANIPULATOR_HANDLE_Z);

	m_pMaterial = new DefaultMaterial();
}

void ManipulatorNode::GenManipulatorHandleVBO(
	DefaultVertexBuffer* pFaceBuffer, 
	DefaultVertexBuffer* pEdgeBuffer, 
	MANIPULATOR_HANDLE handle)
{
	if (pFaceBuffer == nullptr ||
		pEdgeBuffer == nullptr)
	{
		assert(0);
		return;
	}

	vector<vec3> facet;
	vector<int> faceIndex;
	manipulator.GetFaceList(facet, faceIndex, handle);
	pFaceBuffer->Generate(VERTEX_LAYOUT_P);
	pFaceBuffer->SetPosition(GL_TRIANGLES, facet);
	pFaceBuffer->SetIndex(GL_TRIANGLES, faceIndex);

	vector<vec3> edge;
	vector<int> edgeIndex;
	manipulator.GetEdgeList(edge, edgeIndex, handle);
	pEdgeBuffer->Generate(VERTEX_LAYOUT_P);
	pEdgeBuffer->SetPosition(GL_LINES, edge);
	pEdgeBuffer->SetIndex(GL_LINES, edgeIndex);

}

void ManipulatorNode::Draw()
{
	m_pMaterial->SetFixColor(vec4(1, 0, 0, 1));
	m_pMaterial->Draw(m_pFaceBuffers[MANIPULATOR_HANDLE_X]);
	m_pMaterial->Draw(m_pFaceBuffers[MANIPULATOR_HANDLE_X]);

	m_pMaterial->SetFixColor(vec4(0, 1, 0, 1));
	m_pMaterial->Draw(m_pFaceBuffers[MANIPULATOR_HANDLE_Y]);
	m_pMaterial->Draw(m_pFaceBuffers[MANIPULATOR_HANDLE_Y]);

	m_pMaterial->SetFixColor(vec4(0, 0, 1, 1));
	m_pMaterial->Draw(m_pFaceBuffers[MANIPULATOR_HANDLE_Z]);
	m_pMaterial->Draw(m_pFaceBuffers[MANIPULATOR_HANDLE_Z]);
}


void ManipulatorNode::Pick(const vec3& direction, PickResult& result)
{
}
}
