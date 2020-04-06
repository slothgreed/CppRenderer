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
	directionLight->Direction(vec3(1, 1, 1));
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
		modelSpace.Set(vec3(-200), vec3(200));
		auto pVertexBuffer = make_shared<DefaultVertexBuffer>();
		auto pIndexBuffer = make_shared<IndexBuffer>();
		ModelGenerator::CubeSpace(modelSpace, pVertexBuffer.get(), pIndexBuffer.get());
		auto pCubeNode = make_shared<PrimitiveNode>(pVertexBuffer, pIndexBuffer);
		auto pTexture = make_shared<Texture>();
		pTexture->Generate();
		TextureData textureData;
		TextureGenerator::Load("E:\\cgModel\\texture\\SkyBox\\skybox-texture800x600.png", textureData);
		pTexture->Begin();
		pTexture->Set(textureData);
		pTexture->End();
		pCubeNode->GetMaterial()->AddTexture(pTexture);

		m_pScene->AddModelNode(pCubeNode);
	}


	//{
	//	auto moveManipulator = make_shared<ManipulatorNode>();
	//	m_pScene->AddModelNode(moveManipulator);
	//}

	auto axis = make_shared<DefaultVertexBuffer>();
	ModelGenerator::Axis(axis.get());
	auto axisNode = make_shared<PrimitiveNode>(axis);
	m_pScene->AddModelNode(axisNode);

	auto sphere = make_shared<DefaultVertexBuffer>();
	auto sphereIdx = make_shared<IndexBuffer>();
	ModelGenerator::Sphere(10, 10, 10, sphere.get(), sphereIdx.get());
	auto sphereNode = make_shared<PrimitiveNode>(sphere, sphereIdx);
	m_pScene->AddModelNode(sphereNode);


	m_pBackTarget = make_shared<SymbolicRenderTarget>(GL_BACK);
	m_pGeometryPass = make_shared<GeometryPass>();
	m_pGeometryPass->Initialize(640, 480);
}
void BunnyScene::Invoke()
{
	//m_pGeometryPass->Draw(m_pRenderList);
	m_pScene->Bind();
	m_pBackTarget->Begin();
	m_pBackTarget->Clear();
	m_pScene->Draw();
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
}
}