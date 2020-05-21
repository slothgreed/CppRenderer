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

	auto pRenderData = make_shared<RenderData>(
		GL_TRIANGLES,
		make_shared<DefaultVertexBuffer>(),
		make_shared<IndexBuffer>());

	m_pConeNode = make_shared<PrimitiveNode>(pRenderData);
	m_pScene->AddModelNode(m_pConeNode);

	auto pBasicMaterial = make_shared<BasicMaterial>(vec4(0, 0, 0, 1));
	auto pPointData = make_shared<RenderData>(
		GL_POINTS,
		make_shared<DefaultVertexBuffer>());
	pPointData->SetMaterial(pBasicMaterial);
	m_pPointNode = make_shared<PrimitiveNode>(pPointData);
	m_pPointNode->SetState(make_shared<PointState>(5.0f, false));
	m_pScene->AddModelNode(m_pPointNode);

	GenerateVoronoiDiagram();

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
	if (input.Event() == MOUSE_EVENT::MOUSE_EVENT_DOWN)
	{
		if (input.Press() == MOUSE_BUTTON::MOUSE_BUTTON_RIGHT)
		{
			GenerateVoronoiDiagram();
		}
	}
}

void VoronoiScene::GenerateVoronoiDiagram()
{
	vector<vec3> pointPosition;
	GenerateVoronoiPoint(pointPosition, 100);
	m_pPointNode->GetVertexBuffer()->SetPosition(pointPosition);

	vector<vec3> position;
	vector<vec3> color;
	vector<mat4x4> matrix;
	vector<int> index;

	GenerateVoronoiCone(pointPosition, position, color, matrix, index);

	m_pConeNode->GetVertexBuffer()->SetPosition(position);
	m_pConeNode->GetVertexBuffer()->SetColor(color);
	m_pConeNode->GetVertexBuffer()->SetInstanceMatrix(matrix);
	m_pConeNode->GetVertexBuffer()->SetInstanceNum(100);
	m_pConeNode->GetIndexBuffer()->Set(index);
}

void VoronoiScene::GenerateVoronoiPoint(vector<vec3>& position, int size)
{
	position.clear();
	position.resize(size);
	for (int i = 0; i < size; i++)
	{
		float x = Gaccho::rnd(-1000, 1000) / 100.0f;
		float y = Gaccho::rnd(-1000, 1000) / 100.0f;
		position[i] = vec3(x, y, 0);
	}
}

void VoronoiScene::GenerateVoronoiCone(const vector<vec3>& pointPosition, vector<vec3>& position, vector<vec3>& color, vector<mat4x4>& matrix, vector<int>& index)
{
	Cone cone;
	cone.Build(5, 10, 50);
	std::copy(cone.Position().begin(), cone.Position().end(), back_inserter(position));
	std::copy(cone.Index().begin(), cone.Index().end(), back_inserter(index));

	for (int i = 0; i < pointPosition.size(); i++)
	{
		mat4x4 xMatrix = mat4x4(1);
		xMatrix = glm::translate(xMatrix, pointPosition[i]);
		xMatrix = glm::rotate(xMatrix, -pi<float>() / 2, vec3(1, 0, 0));
		matrix.push_back(xMatrix);
		color.push_back(vec3(Gaccho::rnd(0, 255) / 255.0, Gaccho::rnd(0, 255) / 255.0, Gaccho::rnd(0, 255) / 255.0));
	}
}
}