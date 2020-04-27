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
	m_pMaterial = make_shared<DefaultMaterial>();

	for (int i = 0; i < MANIPULATOR_HANDLE_NUM; i++)
	{
		MANIPULATOR_HANDLE handle = (MANIPULATOR_HANDLE)i;
		m_pFaceDatas[handle] = make_shared<RenderData>();
		m_pFaceDatas[handle]->SetMaterial(m_pMaterial);
		m_pEdgeDatas[handle] = make_shared<RenderData>();
		m_pEdgeDatas[handle]->SetMaterial(m_pMaterial);

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
	manipulator.GetFaceList(facet, faceIndex, handle);
	pFaceBuffer->SetPosition(facet);
	pFaceIndexBuffer->Set(faceIndex);
	pFaceData->SetGeometryData(GL_TRIANGLES, pFaceBuffer, pFaceIndexBuffer);

	auto pEdgeBuffer = make_shared<DefaultVertexBuffer>();
	auto pEdgeIndexBuffer = make_shared<IndexBuffer>();
	vector<vec3> edge;
	vector<int> edgeIndex;
	manipulator.GetEdgeList(edge, edgeIndex, handle);
	pEdgeBuffer->SetPosition(edge);
	pEdgeIndexBuffer->Set(edgeIndex);
	pEdgeData->SetGeometryData(GL_LINES, pFaceBuffer, pFaceIndexBuffer);

}

void ManipulatorNode::Draw()
{
	m_pMaterial->SetFixColor(vec4(1, 0, 0, 1));
	m_pFaceDatas[MANIPULATOR_HANDLE_X]->Draw();
	m_pEdgeDatas[MANIPULATOR_HANDLE_X]->Draw();

	m_pMaterial->SetFixColor(vec4(0, 1, 0, 1));
	m_pFaceDatas[MANIPULATOR_HANDLE_Y]->Draw();
	m_pEdgeDatas[MANIPULATOR_HANDLE_Y]->Draw();

	m_pMaterial->SetFixColor(vec4(0, 0, 1, 1));
	m_pFaceDatas[MANIPULATOR_HANDLE_Z]->Draw();
	m_pEdgeDatas[MANIPULATOR_HANDLE_Z]->Draw();
}


}
