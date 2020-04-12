namespace KI
{
TessellationScene::TessellationScene()
{
}

TessellationScene::~TessellationScene()
{
}

void TessellationScene::Initialize(Project* pProject)
{
	m_pScene = make_shared<Scene>();
	m_pScene->Initialize();
	auto pCamera = make_shared<OrthoCamera>();
	pCamera->LookAt(vec3(0, 0, -1), vec3(0), vec3(0, 1, 0));
	pCamera->Ortho(-10, 10, -10, 10, -10, 10);
	m_pScene->SetCamera(pCamera);

	auto pVertexBuffer = make_shared<DefaultVertexBuffer>();
	SampleModelGenerator::BezierLine(pVertexBuffer.get());
	m_pBezierNode = make_shared<PrimitiveNode>(
		pVertexBuffer);


	m_pScene->AddModelNode(m_pBezierNode);

	m_pBackTarget = make_shared<SymbolicRenderTarget>(GL_BACK);
}

void TessellationScene::Invoke()
{

}

void TessellationScene::ProcessMouseEvent(const MouseInput& input)
{

}
}
