namespace KI
{
TessellationScene::TessellationScene()
{
}

TessellationScene::~TessellationScene()
{
}

void TessellationScene::Initialize()
{
	m_pScene = make_shared<Scene>();
	m_pScene->Initialize();
	auto pCamera = make_shared<OrthoCamera>();
	pCamera->LookAt(vec3(0, 0, 1), vec3(0), vec3(0, 1, 0));
	pCamera->Ortho(-3, 3, -3, 3, -3, 3);
	m_pScene->SetCamera(pCamera);

	auto pRenderData = make_shared<RenderData>();
	SampleModelGenerator::BezierLine(pRenderData.get());
	m_pBezierNode = make_shared<BezierLineNode>(pRenderData);


	m_pScene->AddModelNode(m_pBezierNode);

	m_pBackTarget = make_shared<SymbolicRenderTarget>(GL_BACK);
}

void TessellationScene::Invoke()
{
	m_pBackTarget->Begin();
	m_pBackTarget->Clear();
	m_pScene->Bind();
	m_pScene->Draw();
	m_pScene->UnBind();
	m_pBackTarget->End();
}

void TessellationScene::ProcessMouseEvent(const MouseInput& input)
{

}
}
