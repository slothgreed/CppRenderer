namespace KI
{

BunnyScene::~BunnyScene()
{
	for (auto itr = m_pController.begin(); itr != m_pController.end(); itr++)
	{
		delete itr->second;
	}
}

void BunnyScene::Initialize(Project* m_pProject)
{
	m_pCommandManager = make_unique<CommandManager>();
	ShaderUtility::SetShaderDirectory(m_pProject->ProjectDir() + "\\Resource");
	auto shaderDefine = make_shared<DefaultShaderDefine>();
	shaderDefine->SetShaderDefine(VERTEX_LAYOUT_PC);
	m_pDefaultShader = ShaderManager::Instance()->FindOrNew(shaderDefine);

	m_pMouse = make_shared<Mouse>();

	m_pCamera = make_shared<Camera>();
	m_pCamera->LookAt(vec3(0, 0, -2), vec3(0, 0, 0), vec3(0, 1, 0));
	m_pCamera->Perspective(glm::radians(60.0f), 1, 0.01f, 1000);

	m_pController[CONTROLER_TYPE::CAMERA_CONTROLER] = new CameraController();
	m_CurrentController = CONTROLER_TYPE::CAMERA_CONTROLER;
	shared_ptr<IControllerArgs> args = make_shared<CameraControllerArgs>(m_pCamera);
	m_pController[CONTROLER_TYPE::CAMERA_CONTROLER]->SetArgs(args);

	m_pUniformScene = make_shared<UniformScene>();
	m_pUniformScene->Generate();
	SceneData sceneData;
	sceneData.ViewMatrix = m_pCamera->ViewMatrix();
	sceneData.Projection = m_pCamera->Projection();
	m_pUniformScene->Set(sceneData);

	{
		auto polyhedron = make_shared<HalfEdgeModel>();
		polyhedron->Load("E:\\cgModel\\bunny6000.half");

		BDB bdb(vec3(0, 0, 0), vec3(1, 1, 1));
		//polyhedron->GetBDB(bdb);
		m_pCamera->FitToBDB(bdb);

		auto polyNode = make_shared<HalfEdgeDSNode>(polyhedron);

		auto voxelCommandArgs = make_shared<VoxelCommandArgs>(
			this, polyNode->GetModel(), 2);
		
		auto voxelCommand = make_shared<VoxelCommand>(voxelCommandArgs);

		m_pCommandManager->Execute(voxelCommand);
		m_pRenderList.push_back(polyNode);
	}

	{
		auto moveManipulator = make_shared<ManipulatorNode>();
		m_pRenderList.push_back(moveManipulator);
	}

	auto axis = make_shared<DefaultVertexBuffer>();
	ModelGenerator::Axis(axis.get());
	auto axisNode = make_shared<PrimitiveNode>(m_pDefaultShader, axis);
	m_pRenderList.push_back(axisNode);

	m_pBackTarget = make_shared<SymbolicRenderTarget>(GL_BACK);
	m_pGeometryPass = make_shared<GeometryPass>();
	m_pGeometryPass->Initialize(640, 480);
}
void BunnyScene::Invoke()
{
	SceneData sceneData;
	sceneData.ViewMatrix = m_pCamera->ViewMatrix();
	sceneData.Projection = m_pCamera->Projection();
	m_pUniformScene->Set(sceneData);
	m_pUniformScene->Bind();

	m_pGeometryPass->Draw(m_pRenderList);

	m_pBackTarget->Begin();
	m_pBackTarget->Clear();
	for (int i = 0; i < m_pRenderList.size(); i++)
	{
		m_pRenderList[i]->Draw();
	}

	m_pUniformScene->UnBind();
}

void BunnyScene::AddModelNode(shared_ptr<IModelNode> pModelNode)
{
	m_pRenderList.push_back(pModelNode);
}

void BunnyScene::ShowProperty()
{
	m_pCamera->ShowProperty();

	for (int i = 0; i < m_pRenderList.size(); i++)
	{
		m_pRenderList[i]->ShowProperty();
	}
}

void BunnyScene::ProcessMouseEvent(const MouseInput& input)
{
	m_pMouse->ApplyMouseInput(input);
	if (input.Event() == MOUSE_EVENT_WHEEL) {
		m_pController[m_CurrentController]->Wheel(*m_pMouse.get());
	}
	else if (input.Event() == MOUSE_EVENT_MOVE)
	{
		m_pController[m_CurrentController]->Move(*m_pMouse.get());
	}
}
}