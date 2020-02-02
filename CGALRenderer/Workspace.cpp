namespace KI
{

Workspace::Workspace()
{
	
}

Workspace::~Workspace()
{
}

void Workspace::Initialize(Project* m_pProject)
{
	m_pCommandManager = make_unique<CommandManager>();

	ShaderUtility::SetShaderDirectory(m_pProject->ProjectDir() + "\\Resource");
	ShaderBuildInfo buildInfo;
	DefaultShader::GetVertexShaderDefine(VERTEX_LAYOUT::VERTEX_LAYOUT_PC, buildInfo);
	m_pDefaultShader = ShaderManager::Instance()->FindOrNew(buildInfo);

	m_pCamera = make_shared<Camera>();
	m_pCamera->LookAt(vec3(0, 0, -2), vec3(0, 0, 0), vec3(0, 1, 0));
	m_pCamera->Perspective(glm::radians(60.0f), 1, 0.01f, 1000);

	m_pUniformScene = make_shared<UniformScene>();
	m_pUniformScene->Generate();
	SceneData sceneData;
	sceneData.ViewMatrix = m_pCamera->ViewMatrix();
	sceneData.Projection = m_pCamera->Projection();
	m_pUniformScene->Set(sceneData);

	//shared_ptr<CGALModel> polyhedron = make_shared<CGALPolyhedron>();
	//polyhedron->Load("E:\\cgModel\\StanfordBunny.off");

	//shared_ptr<CGALModel> polyhedron = make_shared<CGALGeneralizedMaps>();
	//polyhedron->Load("E:\\cgModel\\StanfordBunny.off");
	//polyhedron->GenSampleModel();

	auto axis = make_shared<DefaultVertexBuffer>();
	ModelGenerator::Axis(axis.get());
	auto axisNode = make_shared<PrimitiveNode>(m_pDefaultShader, axis);
	m_pRenderList.push_back(axisNode);

	ShaderBuildInfo info;
	info.shaderType = SHADER_TYPE_DEFAULT;
	DefaultShader::GetVertexShaderDefine(VERTEX_LAYOUT::VERTEX_LAYOUT_PT, info);
	DefaultShader::GetFragShaderDefine(VERTEX_LAYOUT::VERTEX_LAYOUT_PT, info);

	auto shader = ShaderManager::Instance()->FindOrNew(info);

	auto model = make_shared<DefaultVertexBuffer>();
	//ModelGenerator::RenderPlane(plane.get());
	SpecialUtility::LoadVectorFieldSphere(model.get());
	auto modelNode = make_shared<PrimitiveNode>(shader, model);
	TextureData data;
	TextureGenerator::RandomTexture(8, 15, data);
	auto texture = make_shared<Texture>();
	texture->Generate();
	texture->Begin();
	texture->Set(data);
	texture->End();
	modelNode->GetMaterial()->AddTexture(texture);

	m_pRenderList.push_back(modelNode);

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
	m_pBackTarget->Begin();
	SceneData sceneData;
	sceneData.ViewMatrix = m_pCamera->ViewMatrix();
	sceneData.Projection = m_pCamera->Projection();
	m_pUniformScene->Set(sceneData);
	m_pUniformScene->Bind();

	m_pRenderTarget->Begin();
	m_pRenderTarget->Clear();

	for (int i = 0; i < m_pRenderList.size(); i++)
	{
		m_pRenderList[i]->Draw();
	}
	
	m_pRenderTarget->End();
	m_pPfxRenderer->Draw();

	m_pBackTarget->Begin();
	m_pBackTarget->Clear();
	m_pOutputPlane->Draw();

	m_pUniformScene->UnBind();

}

void Workspace::ShowProperty()
{
	m_pCamera->ShowProperty();

	for (int i = 0; i < m_pRenderList.size(); i++)
	{
		m_pRenderList[i]->ShowProperty();
	}
}
}