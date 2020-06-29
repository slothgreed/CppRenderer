namespace KI
{
ManipulatorNode::ManipulatorNode(MANIPULATOR_TYPE type)
	:m_ManipulatorType(type)
{
	if (m_ManipulatorType == MANIPULATOR_TYPE_MOVE)
	{
		m_pManipulator = make_shared<MoveManipulator>();
	}
	else if(m_ManipulatorType == MANIPULATOR_TYPE_ROTATE)
	{
		assert(0);
		//m_pManipulator = make_shared<RotateManipulator>();
	}
	else if (m_ManipulatorType == MANIPULATOR_TYPE_SCALE)
	{
		assert(0);
		//m_pManipulator = make_shared<ScaleManipulator>();
	}
	else
	{
		assert(0);
	}

	SetRenderData();
}

ManipulatorNode::~ManipulatorNode()
{
}

void ManipulatorNode::ShowProperty()
{
	//assert(0);
}

void ManipulatorNode::SetRenderData()
{
	m_pManipulator->Build();
	m_pShading = make_shared<BasicShading>(vec4(1, 0, 0, 1));

	for (int i = 0; i < MANIPULATOR_HANDLE_NUM; i++)
	{
		MANIPULATOR_HANDLE handle = (MANIPULATOR_HANDLE)i;
		m_pFaceDatas[handle] = make_shared<RenderData>();
		m_pFaceDatas[handle]->SetShading(m_pShading);
		m_pEdgeDatas[handle] = make_shared<RenderData>();
		m_pEdgeDatas[handle]->SetShading(m_pShading);

		GenManipulatorHandleVBO(m_pFaceDatas[handle].get(), m_pEdgeDatas[handle].get(), handle);
	}
}

void ManipulatorNode::GenManipulatorHandleVBO(
	RenderData* pFaceData,
	RenderData* pEdgeData,
	MANIPULATOR_HANDLE handle)
{
	if (pFaceData == nullptr ||
		pEdgeData == nullptr)
	{
		assert(0);
		return;
	}

	auto pFaceBuffer = make_shared<DefaultVertexBuffer>();
	auto pFaceIndexBuffer = make_shared<IndexBuffer>();

	vector<vec3> facet;
	vector<int> faceIndex;
	m_pManipulator->GetFaceList(facet, faceIndex, handle);
	pFaceBuffer->SetPosition(facet);
	pFaceIndexBuffer->Set(faceIndex);
	pFaceData->SetGeometryData(GL_TRIANGLES, pFaceBuffer, pFaceIndexBuffer);

	auto pEdgeBuffer = make_shared<DefaultVertexBuffer>();
	auto pEdgeIndexBuffer = make_shared<IndexBuffer>();
	vector<vec3> edge;
	vector<int> edgeIndex;
	m_pManipulator->GetEdgeList(edge, edgeIndex, handle);
	pEdgeBuffer->SetPosition(edge);
	pEdgeIndexBuffer->Set(edgeIndex);
	pEdgeData->SetGeometryData(GL_LINES, pEdgeBuffer, pFaceIndexBuffer);

}

void ManipulatorNode::DrawCore()
{
	m_pShading->SetColor(vec4(1, 0, 0, 1));
	m_pFaceDatas[MANIPULATOR_HANDLE_X]->Draw();
	m_pEdgeDatas[MANIPULATOR_HANDLE_X]->Draw();

	m_pShading->SetColor(vec4(0, 1, 0, 1));
	m_pFaceDatas[MANIPULATOR_HANDLE_Y]->Draw();
	m_pEdgeDatas[MANIPULATOR_HANDLE_Y]->Draw();

	m_pShading->SetColor(vec4(0, 0, 1, 1));
	m_pFaceDatas[MANIPULATOR_HANDLE_Z]->Draw();
	m_pEdgeDatas[MANIPULATOR_HANDLE_Z]->Draw();
}


}
