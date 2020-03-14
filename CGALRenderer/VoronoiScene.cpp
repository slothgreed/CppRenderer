namespace KI
{

void VoronoiScene::Initialize(Project* m_pProject)
{
	auto pCamera = make_shared<OrthoCamera>();
	pCamera->LookAt(vec3(0, 0, -1), vec3(0), vec3(0, 1, 0));
	pCamera->Ortho(-10, 10, -10, 10, -10, 10);
	m_pCamera = pCamera;

	m_pUnifromScene = make_shared<UniformScene>();
	m_pUnifromScene->Generate();

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
	vector<int> index;
	vector<vec3> color;
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
	m_pConeNode = make_shared<PrimitiveNode>(pVertexBuffer);

	auto pPointVertexBuffer = make_shared<DefaultVertexBuffer>();
	pPointVertexBuffer->Generate(VERTEX_LAYOUT::VERTEX_LAYOUT_P);
	pPointVertexBuffer->SetPosition(GL_POINTS, pointPosition);
	m_pPointNode = make_shared<PrimitiveNode>(pPointVertexBuffer);
	m_pPointNode->GetMaterial()->SetFixColor(vec4(0, 0, 0, 1));
	glPointSize(5);

	m_pBackTarget = make_shared<SymbolicRenderTarget>(GL_BACK);
}

void VoronoiScene::Invoke()
{
	SceneData sceneData;
	sceneData.viewMatrix = m_pCamera->ViewMatrix();
	sceneData.projection = m_pCamera->Projection();
	m_pUnifromScene->Set(sceneData);
	m_pUnifromScene->Bind();
	m_pBackTarget->Begin();
	m_pBackTarget->Clear();
	m_pConeNode->Draw();
	glDisable(GL_DEPTH_TEST);
	m_pPointNode->Draw();
	glEnable(GL_DEPTH_TEST);
	m_pBackTarget->End();
	m_pUnifromScene->UnBind();
}

void VoronoiScene::ProcessMouseEvent(const MouseInput& input)
{
}

}