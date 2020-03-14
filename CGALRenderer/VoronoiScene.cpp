namespace KI
{

void VoronoiScene::Initialize(Project* m_pProject)
{
	m_pScene = make_shared<Scene>();
	m_pScene->Initialize();
	auto pCamera = make_shared<OrthoCamera>();
	pCamera->LookAt(vec3(0, 0, -1), vec3(0), vec3(0, 1, 0));
	pCamera->Ortho(-10, 10, -10, 10, -10, 10);
	m_pScene->SetCamera(pCamera);

	vector<vec3> pointPosition;
	int pointSize = 100;
	for (int i = 0; i < pointSize; i++)
	{
		float x = Gaccho::rnd(-1000, 1000) / 100.0f;
		float y = Gaccho::rnd(-1000, 1000) / 100.0f;
		pointPosition.push_back(vec3(x, y, 0));
	}

	Cone cone;
	vector<vec3> position;
	vector<vec3> color;
	vector<int> index;
	for (int i = 0; i < pointSize; i++)
	{
		cone.Build(5, 10, 50);
		mat4x4 xMatrix = mat4x4(1);
		xMatrix = glm::translate(xMatrix, pointPosition[i]);
		xMatrix = glm::rotate(xMatrix, -pi<float>() / 2, vec3(1, 0, 0));
		cone.Multi(xMatrix);
		std::copy(cone.Position().begin(), cone.Position().end(), back_inserter(position));
		std::copy(cone.Index().begin(), cone.Index().end(), back_inserter(index));
		cone.SetIndexOffset((int)cone.Position().size() * i);
		vector<vec3> coneColor(cone.Position().size(), vec3(Gaccho::rnd(0, 255) / 255.0, Gaccho::rnd(0, 255) / 255.0, Gaccho::rnd(0, 255) / 255.0));
		std::copy(coneColor.begin(), coneColor.end(), back_inserter(color));
	}


	auto pVertexBuffer = make_shared<DefaultVertexBuffer>();
	pVertexBuffer->Generate(VERTEX_LAYOUT::VERTEX_LAYOUT_PC);
	pVertexBuffer->SetPosition(GL_TRIANGLES, position);
	pVertexBuffer->SetColor(color);
	pVertexBuffer->SetIndex(GL_TRIANGLES, index);
	auto pConeNode = make_shared<PrimitiveNode>(pVertexBuffer);
	m_pScene->AddModelNode(pConeNode);

	auto pPointVertexBuffer = make_shared<DefaultVertexBuffer>();
	pPointVertexBuffer->Generate(VERTEX_LAYOUT::VERTEX_LAYOUT_P);
	pPointVertexBuffer->SetPosition(GL_POINTS, pointPosition);
	auto pPointNode = make_shared<PrimitiveNode>(pPointVertexBuffer);
	pPointNode->GetMaterial()->SetFixColor(vec4(0, 0, 0, 1));
	pPointNode->SetState(make_shared<PointState>(5, false));
	m_pScene->AddModelNode(pPointNode);

	m_pBackTarget = make_shared<SymbolicRenderTarget>(GL_BACK);
}

void VoronoiScene::Invoke()
{
	m_pBackTarget->Begin();
	m_pBackTarget->Clear();
	m_pScene->Bind();
	m_pScene->Draw();
	m_pScene->UnBind();
	m_pBackTarget->End();
}

void VoronoiScene::ProcessMouseEvent(const MouseInput& input)
{
}

}