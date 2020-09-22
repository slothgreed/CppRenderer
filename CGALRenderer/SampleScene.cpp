namespace KI
{
SampleScene::SampleScene()
{
}

SampleScene::~SampleScene()
{
	for (auto itr = m_pController.begin(); itr != m_pController.end(); itr++)
	{
		delete itr->second;
	}
}

void SampleScene::Initialize()
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

	//shared_ptr<CGALModel> polyhedron = make_shared<CGALPolyhedron>();
	//polyhedron->Load("E:\\cgModel\\StanfordBunny.off");

	//shared_ptr<CGALModel> polyhedron = make_shared<CGALGeneralizedMaps>();
	//polyhedron->Load("E:\\cgModel\\StanfordBunny.off");
	//polyhedron->GenSampleModel();

	auto axisNode = make_shared<PrimitiveNode>(make_shared<PrimitiveModel>(make_shared<Axis>(AxisArgs())));
	m_pScene->AddModelNode(axisNode);

	//ModelGenerator::Plane(plane.get());
	auto model = make_shared<RenderData>();
	SpecialUtility::LoadVectorFieldSphere(model.get());

	auto pModelNode = make_shared<PrimitiveNode>(model);
	TextureData data;
	TextureGenerator::RandomTexture(8, 15, data);
	auto texture = make_shared<Texture>();
	texture->Generate();
	texture->Begin();
	texture->Set(data);
	texture->End();
	auto pBasicShading = make_shared<BasicShading>(texture);
	model->SetShading(pBasicShading);
	m_pScene->AddModelNode(pModelNode);

	m_pRenderTarget = make_shared<RenderTarget>();
	m_pRenderTarget->Initialize(1, 640, 480);

	m_pBackTarget = make_shared<SymbolicRenderTarget>(GL_BACK);
	//auto subdivArgs = make_shared<SubdivisionCommandArgs>(polyhedron);
	//auto subdivCommand = make_shared<SubdivisionCommand>(subdivArgs);
	//m_pCommandManager->Execute(subdivCommand);

	auto pSSLIC = make_shared<SSLICEffect>();
	pSSLIC->Initialize(64, 64);
	pSSLIC->SetModelNode(pModelNode);

	auto pGrayScale = make_shared<GrayScaleEffect>();
	pGrayScale->Initialize(640, 480);
	pGrayScale->SetTexture(m_pRenderTarget->ColorTexture(FRAMEBUFFER_COLOR_ATTACHMENT0));

	m_pPfxRenderer = make_shared<PfxRenderer>();
	m_pPfxRenderer->AddPostEffect(pSSLIC);
	m_pPfxRenderer->AddPostEffect(pGrayScale);

	m_pOutputPlane = make_shared<PfxPlane>();
	m_pOutputPlane->SetTexture(m_pRenderTarget->ColorTexture(FRAMEBUFFER_COLOR_ATTACHMENT0));
	m_pOutputPlane->Initialize();
}

void SampleScene::Invoke()
{
	m_pRenderTarget->Begin();
	{
		m_pRenderTarget->Clear();

		m_pScene->Bind();
		{
			m_pScene->Draw();
		}
		m_pScene->UnBind();
	}
	m_pRenderTarget->End();

	m_pPfxRenderer->Draw();

	m_pBackTarget->Begin();
	{
		m_pBackTarget->Clear();
		m_pOutputPlane->Draw();
	}
	m_pBackTarget->End();
}

void SampleScene::ProcessMouseEvent(const MouseInput& input)
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