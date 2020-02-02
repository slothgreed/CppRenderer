namespace KI
{

HalfEdgeProperty::HalfEdgeProperty(HalfEdgeDS* model)
{
	Build(model);
}

void HalfEdgeProperty::Build(HalfEdgeDS* model)
{
	m_pVertexBuffer = make_shared<DefaultVertexBuffer>();
	m_pVertexBuffer->Generate(VERTEX_LAYOUT::VERTEX_LAYOUT_PC);

	vector<vec3> position;
	vector<vec3> color;
	GetVBOData(model, position, color, true);
	position.resize(model->EdgeList().size() * 2);
	color.resize(model->EdgeList().size() * 2);

	m_pVertexBuffer->SetPosition(GL_LINES, position);
	m_pVertexBuffer->SetColor(color);

	ShaderBuildInfo buildInfo;
	DefaultShader::GetVertexShaderDefine(VERTEX_LAYOUT_PC, buildInfo);
	m_pShader = ShaderManager::Instance()->FindOrNew(buildInfo);
}

void HalfEdgeProperty::Update(void* model)
{
	vector<vec3> position;
	vector<vec3> color;
	GetVBOData((HalfEdgeDS*)model, position, color, false);
	m_pVertexBuffer->SetPosition(GL_LINES, position);
}

void HalfEdgeProperty::GetVBOData(HalfEdgeDS* model, vector<vec3>& position, vector<vec3>& color, bool needColor)
{
	position.resize(model->EdgeList().size() * 2);
	if (needColor)
	{
		color.resize(model->EdgeList().size() * 2);
	}

	for (int i = 0; i < model->FaceList().size(); i++)
	{
		auto itr = FaceAroundEdgeIterator(model->FaceList()[i].get());

		while (itr.HasNext())
		{
			auto edge = itr.Current();
			vec3 start = edge->Start()->Position();
			vec3 end = edge->End()->Position();
			vec3 centroid = edge->Face()->Centroid();

			start = start - (centroid * 0.8f) + centroid;
			end = end - (centroid * 0.8f) + centroid;

			position.push_back(start);
			position.push_back(end);
			if (needColor)
			{
				color.push_back(vec3(0, 0, 1));
				color.push_back(vec3(1, 0, 0));
			}

			itr.Next();
		}
	}
}

void HalfEdgeProperty::Draw()
{
	m_pShader->Use();
	m_pVertexBuffer->Draw();
	m_pShader->UnUse();
}
}