namespace KI
{
namespace RenderModel
{
ManipulatorNode::ManipulatorNode(MANIPULATOR_TYPE type)
	:m_ManipulatorType(type),m_SelectIndex(-1)
{
	if (m_ManipulatorType == MANIPULATOR_TYPE_MOVE)
	{
		m_pManipulator = make_shared<MoveManipulator>();
	}
	else if(m_ManipulatorType == MANIPULATOR_TYPE_ROTATE)
	{
		m_pManipulator = make_shared<RotateManipulator>();
	}
	else if (m_ManipulatorType == MANIPULATOR_TYPE_SCALE)
	{
		m_pManipulator = make_shared<ScaleManipulator>();
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

void ManipulatorNode::SetRenderData()
{
	m_pManipulator->Build();
	m_pShading = make_shared<BasicShading>(vec4(1, 0, 0, 1));

	for (int i = 0; i < MANIPULATOR_HANDLE_NUM; i++)
	{
		MANIPULATOR_HANDLE handle = (MANIPULATOR_HANDLE)i;
		auto pFaceDatas = make_shared<RenderData>();
		pFaceDatas->SetShading(m_pShading);

		GenManipulatorHandleVBO(pFaceDatas.get(), handle);

		AddRenderData(i, pFaceDatas);
	}
}

void ManipulatorNode::GenManipulatorHandleVBO(
	RenderData* pFaceData,
	MANIPULATOR_HANDLE handle)
{
	if (pFaceData == nullptr)
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
	pFaceData->SetGeometryData(PRIM_TYPE_TRIANGLES, pFaceBuffer, pFaceIndexBuffer);
}

void ManipulatorNode::PreDraw(shared_ptr<UniformStruct> pUniform, int index)
{
	if (index == MANIPULATOR_HANDLE_X)
	{
		m_pShading->SetColor(vec4(1, 0, 0, 1));
	}
	else if (index == MANIPULATOR_HANDLE_Y)
	{
		m_pShading->SetColor(vec4(0, 1, 0, 1));
	}
	else if (index == MANIPULATOR_HANDLE_Z)
	{
		m_pShading->SetColor(vec4(0, 0, 1, 1));
	}
	else
	{
		assert(0);
	}
}

void ManipulatorNode::ClearSelect() 
{
	if (m_SelectIndex == -1) {
		return;
	}

	if (GetRenderData(m_SelectIndex)->HasRenderRegion())
	{
		GetRenderData(m_SelectIndex)->ClearRenderRegion();
	}

	GetRenderData(m_SelectIndex)->SetShading(m_pShading);
	m_SelectIndex = -1;
}
void ManipulatorNode::AddSelect(PICK_TYPE type, shared_ptr<IShading> pShading, int pickId, int first, int count)
{
	if (m_SelectIndex != -1) {
		ClearSelect();
	}

	if (type != PICK_TYPE::PICK_TYPE_OBJECT)
	{
		assert(0);
	}

	for (int i = 0; i < GetRenderDataNum(); i++)
	{
		if (GetRenderData(i)->GetPickID() == pickId)
		{
			GetRenderData(i)->SetShading(pShading);
			m_SelectIndex = i;
		}
	}
	
}


}
}
