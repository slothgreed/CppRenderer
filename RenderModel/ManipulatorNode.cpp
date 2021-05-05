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
		RenderData pFaceDatas;
		pFaceDatas.SetShading(m_pShading);

		GenManipulatorHandleVBO(pFaceDatas, handle);

		m_pManipulatorData[i] = pFaceDatas;
	}
}

void ManipulatorNode::GenManipulatorHandleVBO(
	RenderData& pFaceData,
	MANIPULATOR_HANDLE handle)
{
	auto pFaceBuffer = make_shared<DefaultVertexBuffer>();
	auto pFaceIndexBuffer = make_shared<IndexBuffer>();

	vector<vec3> facet;
	vector<int> faceIndex;
	m_pManipulator->GetFaceList(facet, faceIndex, handle);
	pFaceBuffer->SetPosition(facet);
	pFaceIndexBuffer->Set(faceIndex);
	pFaceData.SetGeometryData(PRIM_TYPE_TRIANGLES, pFaceBuffer, pFaceIndexBuffer);
}

void ManipulatorNode::FixedShaderDraw(shared_ptr<IShader> pShader, shared_ptr<IShading> pShading, shared_ptr<UniformStruct> pUniform)
{
	if (Visible() == false)
	{
		return;
	}
	else
	{
		for (int i = 0; i < MANIPULATOR_HANDLE_NUM; i++) {
			if (pUniform != NULL)
			{
				if (pUniform->GetModel() != NULL)
				{
					pUniform->GetModel()->SetModelMatrix(GetModelMatrix());
					pUniform->GetModel()->SetObjectId(m_pManipulatorData[i].GetPickID());
					pUniform->GetModel()->Bind();
				}
			}

			m_pManipulatorData[i].Draw(pShader, pShading, pUniform);
		}
	}
}

void ManipulatorNode::Draw(shared_ptr<UniformStruct> pUniform)
{
	if (Visible() == false)
	{
		return;
	}
	else
	{
		for (int i = 0; i < MANIPULATOR_HANDLE_NUM; i++) {
			if (i == MANIPULATOR_HANDLE_X)
			{
				m_pShading->SetColor(vec4(1, 0, 0, 1));
			}
			else if (i == MANIPULATOR_HANDLE_Y)
			{
				m_pShading->SetColor(vec4(0, 1, 0, 1));
			}
			else if (i == MANIPULATOR_HANDLE_Z)
			{
				m_pShading->SetColor(vec4(0, 0, 1, 1));
			}

			if (pUniform != NULL)
			{
				if (pUniform->GetModel() != NULL)
				{
					pUniform->GetModel()->SetModelMatrix(GetModelMatrix());
					pUniform->GetModel()->SetObjectId(m_pManipulatorData[i].GetPickID());
					pUniform->GetModel()->Bind();
				}
			}

			m_pManipulatorData[i].Draw(pUniform);
		}
	}
}

void ManipulatorNode::ClearSelect() 
{
	if (m_SelectIndex == -1) {
		return;
	}


	for (int i = 0; i < MANIPULATOR_HANDLE_NUM; i++) {
		if (m_pManipulatorData[i].HasRenderRegion())
		{
			m_pManipulatorData[i].ClearRenderRegion();
		}
	}

	m_pManipulatorData[m_SelectIndex].SetShading(m_pShading);
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

	for (int i = 0; i < MANIPULATOR_HANDLE_NUM; i++) {
		if (m_pManipulatorData[i].GetPickID() == pickId)
		{
			m_pManipulatorData[i].SetShading(pShading);
			m_SelectIndex = i;
		}
	}
}

void ManipulatorNode::SetPickID(int start, int* next)
{
	for (int i = 0; i < MANIPULATOR_HANDLE_NUM; i++) {
		m_pManipulatorData[i].SetPickID(start);
		start++;
	}


	*next = start;
}

bool ManipulatorNode::HasPickID(int id)
{
	for (int i = 0; i < MANIPULATOR_HANDLE_NUM; i++) {
		if (m_pManipulatorData[i].GetPickID() == id)
		{
			return true;
		}
	}

	return false;
}

}
}
