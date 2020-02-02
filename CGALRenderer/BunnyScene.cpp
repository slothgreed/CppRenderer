namespace KI
{

void BunnyScene::Initialize(Project* m_pProject)
{
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

	{
		shared_ptr<IModel> polyhedron = make_shared<HalfEdgeModel>();
		polyhedron->Load("E:\\cgModel\\bunny6000.half");

		BDB bdb(vec3(0, 0, 0), vec3(1, 1, 1));
		polyhedron->GetBDB(bdb);
		m_pCamera->FitToBDB(bdb);

		auto polyNode = make_shared<ModelNode>(polyhedron);
		m_pRenderList.push_back(polyNode);
	}

	auto axis = make_shared<DefaultVertexBuffer>();
	ModelGenerator::Axis(axis.get());
	auto axisNode = make_shared<PrimitiveNode>(m_pDefaultShader, axis);
	m_pRenderList.push_back(axisNode);

	ShaderBuildInfo info;
	info.shaderType = SHADER_TYPE_DEFAULT;
	DefaultShader::GetVertexShaderDefine(VERTEX_LAYOUT::VERTEX_LAYOUT_PT, info);
	DefaultShader::GetFragShaderDefine(VERTEX_LAYOUT::VERTEX_LAYOUT_PT, info);

	m_pBackTarget = make_shared<SymbolicRenderTarget>(GL_BACK);
	
}
void BunnyScene::Invoke()
{
	m_pBackTarget->Begin();
	SceneData sceneData;
	sceneData.ViewMatrix = m_pCamera->ViewMatrix();
	sceneData.Projection = m_pCamera->Projection();
	m_pUniformScene->Set(sceneData);
	m_pUniformScene->Bind();

	m_pBackTarget->Clear();
	for (int i = 0; i < m_pRenderList.size(); i++)
	{
		m_pRenderList[i]->Draw();
	}

	m_pUniformScene->UnBind();

}

void BunnyScene::ShowProperty()
{
	return;
}
}