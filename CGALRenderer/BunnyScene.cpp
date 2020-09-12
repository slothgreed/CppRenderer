namespace KI
{
BunnyScene::~BunnyScene()
{
	for (auto itr = m_pController.begin(); itr != m_pController.end(); itr++)
	{
		delete itr->second;
	}
}

void BunnyScene::Initialize()
{
	m_pCommandManager = make_unique<CommandManager>();
	m_pMouse = make_shared<Mouse>();

	m_pScene = make_shared<Scene>();
	m_pScene->Initialize();

	auto pCamera = make_shared<PerspectiveCamera>();
	pCamera->LookAt(vec3(0, 0, -2), vec3(0, 0, 0), vec3(0, 1, 0));
	pCamera->Perspective(glm::radians(60.0f), 1, 0.01f, 1000);
	m_pScene->SetCamera(pCamera);

	m_pController[CONTROLER_TYPE::CAMERA_CONTROLER] = new CameraController();
	m_CurrentController = CONTROLER_TYPE::CAMERA_CONTROLER;
	shared_ptr<IControllerArgs> args = make_shared<CameraControllerArgs>(pCamera);
	m_pController[CONTROLER_TYPE::CAMERA_CONTROLER]->SetArgs(args);


	auto directionLight = make_shared<DirectionLight>();
	directionLight->SetDirection(vec3(1, 1, 1));
	m_pScene->AddLight(directionLight);

	BDB modelSpace(vec3(0), vec3(1));
	{
		auto polyhedron = make_shared<HalfEdgeModel>();
		polyhedron->Load("E:\\cgModel\\bunny6000.half");

		polyhedron->GetBDB(modelSpace);

		auto polyNode = make_shared<HalfEdgeDSNode>(polyhedron);

		auto voxelCommandArgs = make_shared<VoxelCommandArgs>(
			m_pScene.get(), polyNode->GetModel(), 100);

		//auto voxelCommand = make_shared<VoxelCommand>(voxelCommandArgs);

		//m_pCommandManager->Execute(voxelCommand);
		m_pScene->AddModelNode(polyNode);
	}
	pCamera->FitToBDB(modelSpace);

	{
		auto pTexture = make_shared<Texture>();
		pTexture->Generate();
		TextureData textureData;
		TextureGenerator::Load("E:\\cgModel\\texture\\SkyBox\\skybox-texture800x600.png", textureData);
		pTexture->Begin();
		pTexture->Set(textureData);
		pTexture->End();
		auto pBasicShading = make_shared<BasicShading>(pTexture);
		auto pCubeNode = make_shared<PrimitiveNode>(
			make_shared<PrimitiveModel>(
				make_shared<CubeSpace>(
					CubeSpaceArgs(BDB(vec3(-200), vec3(200))))),
			pBasicShading);
		m_pScene->AddModelNode(pCubeNode);
	}

	//{
	//	auto moveManipulator = make_shared<ManipulatorNode>();
	//	m_pScene->AddModelNode(moveManipulator);
	//}

	auto axisNode = make_shared<PrimitiveNode>(make_shared<PrimitiveModel>(make_shared<Axis>(AxisArgs())));
	m_pScene->AddModelNode(axisNode);

	m_pBackTarget = make_shared<SymbolicRenderTarget>(GL_BACK);
	m_pGeometryPath = make_shared<GeometryPath>();
	m_pGeometryPath->Initialize(640, 480);

	//m_pPickPath = make_shared<PickPath>();
	//m_pPickPath->Initialize(640, 480);
	//m_pPickPath->ResetPickID(m_pScene->ModelNodes());
}
void BunnyScene::Invoke()
{
	//m_pGeometryPass->Draw(m_pRenderList);
	m_pScene->Bind();
	m_pBackTarget->Begin();
	m_pBackTarget->Clear();
	m_pScene->Draw();
	//m_pPickPath->Draw(m_pScene->ModelNodes());
	m_pScene->UnBind();
}

void BunnyScene::ProcessMouseEvent(const MouseInput& input)
{
	m_pMouse->ApplyMouseInput(input);
	if (input.Event() == MOUSE_EVENT_WHEEL)
	{
		m_pController[m_CurrentController]->Wheel(*m_pMouse.get());
	}
	else if (input.Event() == MOUSE_EVENT_MOVE)
	{
		m_pController[m_CurrentController]->Move(*m_pMouse.get());
	}
	else if (input.Event() == MOUSE_EVENT_DOWN)
	{
		//m_pCommandManager->Execute(
		//	make_shared<SelectCommand>(
		//		make_shared<SelectCommandArgs>(
		//			GetViewport(),
		//			m_pScene,
		//			input.Position()))
		//);
	}
}
}