namespace KI
{
PrimitiveScene::~PrimitiveScene()
{
	for (auto itr = m_pController.begin(); itr != m_pController.end(); itr++)
	{
		delete itr->second;
	}
}

void PrimitiveScene::Initialize()
{
	m_pCommandManager = make_unique<CommandManager>();
	m_pMouse = make_shared<Mouse>();

	m_pScene = make_shared<Scene>();
	m_pScene->Initialize();

	auto pCamera = make_shared<PerspectiveCamera>();
	pCamera->LookAt(vec3(0, 0, 2), vec3(0, 0, 0), vec3(0, 1, 0));
	pCamera->Perspective(glm::radians(60.0f), 1, 0.01f, 1000);
	m_pScene->SetCamera(pCamera);

	m_pController[CONTROLER_TYPE::CAMERA_CONTROLER] = new CameraController();
	m_CurrentController = CONTROLER_TYPE::CAMERA_CONTROLER;
	shared_ptr<IControllerArgs> args = make_shared<CameraControllerArgs>(pCamera);
	m_pController[CONTROLER_TYPE::CAMERA_CONTROLER]->SetArgs(args);

	// manipulator rendering
	{
		auto pMoveManipulator = make_shared<MoveManipulator>();
		pMoveManipulator->Build();
		auto pManipulatorNode = make_shared<ManipulatorNode>(MANIPULATOR_TYPE_ROTATE);
		m_pScene->AddModelNode(pManipulatorNode);
	}

	// sphere rendering
	{

		auto pTexture = make_shared<Texture>();
		pTexture->Generate();
		TextureData textureData;
		//TextureGenerator::RandomTexture(8, 255, textureData);
		TextureGenerator::Load("E:\\cgModel\\texture\\SkyBox\\moon1024.png", textureData);
		//TextureGenerator::Load("E:\\cgModel\\texture\\SkyBox\\earth2048.png", textureData);
		pTexture->Begin();
		pTexture->Set(textureData);
		pTexture->End();

		auto pBasicShading = make_shared<PickShading>();
		auto sphereNode = make_shared<PrimitiveNode>(
			make_shared<PrimitiveModel>(
				make_shared<Sphere>(SphereArgs(vec3(0), 1, 36, 36))),
			pBasicShading);
		m_pScene->AddModelNode(sphereNode);
	}

	// icosahedron rendring
	{
		auto pPrimitiveNode = make_shared<PrimitiveNode>(
			make_shared<PrimitiveModel>(
				make_shared<Icosahedron>(IcosahedronArgs()))
			,make_shared<PickShading>());
		m_pScene->AddModelNode(pPrimitiveNode);
	}

	// Cylinder 
	{
		auto pCylinderNode = make_shared<PrimitiveNode>(
			make_shared<PrimitiveModel>(
				make_shared<Cylinder>(CylinderArgs(5, 1, 5, 10)))
			, make_shared<VertexShading>(VERTEX_SHADING_TYPE::VERTEX_SHADING_POSITION));
		m_pScene->AddModelNode(pCylinderNode);
	}

	// Torus rendering
	{
		auto pTorusNode = make_shared<PrimitiveNode>(
			make_shared<PrimitiveModel>(
				make_shared<Torus>(
					TorusArgs(0.5f,1.0f,32,32)))
			,make_shared<VertexShading>(VERTEX_SHADING_TYPE::VERTEX_SHADING_NORMAL));
		m_pScene->AddModelNode(pTorusNode);
	}

	// quad rendering
	{
		auto pPlaneNode = make_shared<PrimitiveNode>(
			make_shared<PrimitiveModel>(
				make_shared<Quad>(
					QuadArgs(vec2(-1), vec2(1)))));
		m_pScene->AddModelNode(pPlaneNode);
	}

	// directional light
	{
		auto pDirectionLightNode =
			make_shared<PrimitiveNode>(
				make_shared<PrimitiveModel>(
					make_shared<DirectionalLightModel>()));
		m_pScene->AddModelNode(pDirectionLightNode);
	}

	// sphere lambert
	{
		auto pLambertShading = make_shared<LambertShading>(vec4(1, 0, 0, 1));
		auto sphereNode = make_shared<PrimitiveNode>(
			make_shared<PrimitiveModel>(make_shared<Sphere>(SphereArgs(vec3(0), 1, 36, 36))), pLambertShading);
		m_pScene->AddModelNode(sphereNode);

		auto pLight = make_shared<DirectionLight>();
		pLight->SetAmbient(vec4(0, 1, 0, 1));
		pLight->SetDirection(vec3(1, 1, 1));

		m_pScene->AddLight(pLight);
	}

	// sphere phong
	{
		auto pPhongShading =
			make_shared<PhongShading>(
				PHONG_SHADING_TYPE_BLIN,
				SHADING_COLOR_TYPE_VERTEXCOLOR,
				ADSMaterial());
		pPhongShading->SetColor(vec4(1, 0, 0, 1));
		auto sphereNode = make_shared<PrimitiveNode>(
			make_shared<PrimitiveModel>(make_shared<Sphere>(SphereArgs(vec3(0), 1, 36, 36))), pPhongShading);

		m_pScene->AddModelNode(sphereNode);
	}

	// axis
	{
		auto axisNode = make_shared<PrimitiveNode>(
			make_shared<PrimitiveModel>(make_shared<Axis>(AxisArgs(vec3(0), vec3(1)))));
		m_pScene->AddModelNode(axisNode);

	}

	// grid
	{
		auto grid = make_shared<Grid>(GridArgs(vec2(44, 4), vec2(2, 0.2)));
		auto gridNode = make_shared<PrimitiveNode>(make_shared<PrimitiveModel>(grid));
		m_pScene->AddModelNode(gridNode);
	}

	//BDB bdb(vec3(0), vec3(2));
	//pCamera->FitToBDB(bdb);

	m_pBackTarget = make_shared<SymbolicRenderTarget>(GL_BACK);

	m_currentPrimitive = 0;
	ShowPrimitive(m_currentPrimitive);

	m_pPickPath = make_shared<PickPath>();
	m_pPickPath->Initialize(640, 480);
	m_pPickPath->ResetPickID(m_pScene);

	m_pOutputPath = make_shared<OutputPath>();
	m_pOutputPath->Initialize(640, 480);
	m_pOutputPath->SetTexture(m_pPickPath->GetPickTexture());
	m_pPlane = make_shared<RenderData>();
	ModelGenerator::Plane(m_pPlane.get(), VERTEX_LAYOUT::VERTEX_LAYOUT_TEXCOORD);
}
void PrimitiveScene::Invoke()
{
	m_pBackTarget->Begin();
	m_pBackTarget->Clear();
	m_pScene->Bind();
	m_pScene->Draw();
	m_pScene->UnBind();
	//m_pPickPath->Draw(m_pScene);
	//m_pOutputPath->Draw(m_pBackTarget, m_pPlane);
}

void PrimitiveScene::NextModel()
{
	m_currentPrimitive = (m_currentPrimitive + 1) % m_pScene->ModelNum();

	ShowPrimitive(m_currentPrimitive);
}

void PrimitiveScene::PreviewModel()
{
	if (m_currentPrimitive == 0)
	{
		m_currentPrimitive = m_pScene->ModelNum() - 1;
	}
	else
	{
		m_currentPrimitive = m_currentPrimitive - 1;
	}

	ShowPrimitive(m_currentPrimitive);
}

void PrimitiveScene::ShowPrimitive(int index)
{
	SceneModelIterator itr(m_pScene.get());
	for (; itr.HasNext(); itr.Next())
	{
		if (itr.Index() == index)
		{
			itr.Current().SetVisible(true);
		}
		else
		{
			itr.Current().SetVisible(false);
		}
	}
	
}
void PrimitiveScene::ProcessMouseEvent(const MouseInput& input)
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
		if (input.Press(MOUSE_BUTTON_LEFT))
		{
			m_pCommandManager->Execute(
				make_shared<PickCommand>(
					make_shared<SelectCommandArgs>(
						GetViewport(),
						m_pScene,
						input.Position())));
		}
		else
		{
			if (input.Press(MOUSE_BUTTON_RIGHT))
			{
				NextModel();
				//m_pCommandManager->Execute(
				//	make_shared<SaveImageCommand>(
				//		make_shared<SaveImageCommandArgs>(
				//			m_pBackTarget,"E:\\MyProgram\\KIProject\\CGALRenderer\\test.bmp")));
			}
		}
	}
}
}