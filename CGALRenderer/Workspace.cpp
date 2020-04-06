namespace KI
{
Workspace::Workspace()
{
}

Workspace::~Workspace()
{
	for (auto itr = m_pController.begin(); itr != m_pController.end(); itr++)
	{
		delete itr->second;
	}
}

void Workspace::Initialize(Project* m_pProject)
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

	auto axis = make_shared<DefaultVertexBuffer>();
	ModelGenerator::Axis(axis.get());
	auto axisNode = make_shared<PrimitiveNode>(axis);
	m_pScene->AddModelNode(axisNode);

	auto model = make_shared<DefaultVertexBuffer>();
	//ModelGenerator::RenderPlane(plane.get());
	SpecialUtility::LoadVectorFieldSphere(model.get());
	auto pModelNode = make_shared<PrimitiveNode>(model);
	TextureData data;
	TextureGenerator::RandomTexture(8, 15, data);
	auto texture = make_shared<Texture>();
	texture->Generate();
	texture->Begin();
	texture->Set(data);
	texture->End();
	pModelNode->GetMaterial()->AddTexture(texture);
	m_pScene->AddModelNode(pModelNode);

	m_pRenderTarget = make_shared<RenderTarget>();
	m_pRenderTarget->Initialize(1, 640, 480);

	m_pBackTarget = make_shared<SymbolicRenderTarget>(GL_BACK);
	//auto subdivArgs = make_shared<SubdivisionCommandArgs>(polyhedron);
	//auto subdivCommand = make_shared<SubdivisionCommand>(subdivArgs);
	//m_pCommandManager->Execute(subdivCommand);

	auto pSSLIC = make_shared<SSLICEffect>();
	pSSLIC->Initialize();
	pSSLIC->SetDrawModel(model);

	auto pGrayScale = make_shared<GrayScaleEffect>();
	pGrayScale->Initialize();
	pGrayScale->SetTexture(m_pRenderTarget->ColorTexture(0));

	m_pPfxRenderer = make_shared<PfxRenderer>();
	m_pPfxRenderer->AddPostEffect(pSSLIC);
	m_pPfxRenderer->AddPostEffect(pGrayScale);

	auto outputMaterial = make_shared<OutputMaterial>();
	m_pOutputPlane = make_shared<PfxPlane>(outputMaterial);
	m_pOutputPlane->Initialize();
	outputMaterial->AddColorTexture(m_pRenderTarget->ColorTexture(0));
}

void Workspace::Invoke()
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

void Workspace::ProcessMouseEvent(const MouseInput& input)
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