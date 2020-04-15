namespace KI
{
ManipulatorNode::ManipulatorNode()
{
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
	manipulator.Build();
	m_pFaceDatas[MANIPULATOR_HANDLE_X] = make_shared<RenderData>();
	m_pFaceDatas[MANIPULATOR_HANDLE_Y] = make_shared<RenderData>();
	m_pFaceDatas[MANIPULATOR_HANDLE_Z] = make_shared<RenderData>();

	m_pEdgeDatas[MANIPULATOR_HANDLE_X] = make_shared<RenderData>();
	m_pEdgeDatas[MANIPULATOR_HANDLE_Y] = make_shared<RenderData>();
	m_pEdgeDatas[MANIPULATOR_HANDLE_Z] = make_shared<RenderData>();

	GenManipulatorHandleVBO(
		m_pFaceDatas[MANIPULATOR_HANDLE_X].get(),
		m_pEdgeDatas[MANIPULATOR_HANDLE_X].get(),
		MANIPULATOR_HANDLE::MANIPULATOR_HANDLE_X);
	GenManipulatorHandleVBO(
		m_pFaceDatas[MANIPULATOR_HANDLE_Y].get(),
		m_pEdgeDatas[MANIPULATOR_HANDLE_Y].get(),
		MANIPULATOR_HANDLE::MANIPULATOR_HANDLE_Y);

	GenManipulatorHandleVBO(
		m_pFaceDatas[MANIPULATOR_HANDLE_Z].get(),
		m_pEdgeDatas[MANIPULATOR_HANDLE_Z].get(),
		MANIPULATOR_HANDLE::MANIPULATOR_HANDLE_Z);

	m_pMaterial = make_shared<DefaultMaterial>();
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
	manipulator.GetFaceList(facet, faceIndex, handle);
	pFaceBuffer->SetPosition(facet);
	pFaceIndexBuffer->Set(faceIndex);
	pFaceData->Set(GL_TRIANGLES, pFaceBuffer, pFaceIndexBuffer);

	auto pEdgeBuffer = make_shared<DefaultVertexBuffer>();
	auto pEdgeIndexBuffer = make_shared<IndexBuffer>();
	vector<vec3> edge;
	vector<int> edgeIndex;
	manipulator.GetEdgeList(edge, edgeIndex, handle);
	pEdgeBuffer->SetPosition(edge);
	pEdgeIndexBuffer->Set(edgeIndex);
	pEdgeData->Set(GL_LINES, pFaceBuffer, pFaceIndexBuffer);

}

void ManipulatorNode::Draw()
{
	m_pMaterial->SetFixColor(vec4(1, 0, 0, 1));
	m_pMaterial->Draw(m_pFaceDatas[MANIPULATOR_HANDLE_X].get());
	m_pMaterial->Draw(m_pEdgeDatas[MANIPULATOR_HANDLE_X].get());

	m_pMaterial->SetFixColor(vec4(0, 1, 0, 1));
	m_pMaterial->Draw(m_pFaceDatas[MANIPULATOR_HANDLE_Y].get());
	m_pMaterial->Draw(m_pEdgeDatas[MANIPULATOR_HANDLE_Y].get());

	m_pMaterial->SetFixColor(vec4(0, 0, 1, 1));
	m_pMaterial->Draw(m_pFaceDatas[MANIPULATOR_HANDLE_Z].get());
	m_pMaterial->Draw(m_pEdgeDatas[MANIPULATOR_HANDLE_Z].get());
}


}
