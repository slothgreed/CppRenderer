namespace KI
{

HalfEdgeProperty::HalfEdgeProperty()
{
}

void HalfEdgeProperty::Build(IModel* model)
{
	HalfEdgeModel* pModel = nullptr;
	if (model->Type() == MODEL_TYPE_HALF_EDGE)
	{
		pModel = (HalfEdgeModel*)model;
	}
	else
	{
		assert(0);
	}

	m_pVertexBuffer = make_shared<DefaultVertexBuffer>();

	vector<vec3> position;
	vector<vec3> color;
	GetVBOData(pModel->GetHalfEdgeDS().get(), position, color, true);
	position.resize(pModel->GetHalfEdgeDS()->EdgeList().size() * 2);
	color.resize(pModel->GetHalfEdgeDS()->EdgeList().size() * 2);

	m_pVertexBuffer->SetPosition(GL_LINES, position);
	m_pVertexBuffer->SetColor(color);

	auto pBuildInfo = make_shared<IShaderBuildInfo>(SHADER_TYPE_DEFAULT);
	auto pVertexCode = make_shared<DefaultVertexCode>();
	pVertexCode->SetShaderDefine(m_pVertexBuffer->Layout());
	pBuildInfo->SetVertexCode(pVertexCode);
	pBuildInfo->SetFragCode(make_shared<DefaultFragCode>());
	m_pShader = ShaderManager::Instance()->FindOrNew(pBuildInfo);

}

void HalfEdgeProperty::Update(IModel* model)
{
	vector<vec3> position;
	vector<vec3> color;
	HalfEdgeModel* pModel = nullptr;
	if (model->Type() == MODEL_TYPE_HALF_EDGE)
	{
		pModel = (HalfEdgeModel*)model;
	}
	else
	{
		assert(0);
	}

	GetVBOData(pModel->GetHalfEdgeDS().get(), position, color, false);
	m_pVertexBuffer->SetPosition(GL_LINES, position);
}

void HalfEdgeProperty::GetVBOData(HalfEdgeDS* model, vector<vec3>& position, vector<vec3>& color, bool needColor)
{
	position.resize(model->EdgeList().size() * 2);
	if (needColor)
	{
		color.resize(model->EdgeList().size() * 2);
	}

	int counter = 0;
	for (int i = 0; i < model->FaceList().size(); i++)
	{
		auto itr = FaceAroundEdgeIterator(model->FaceList()[i].get());

		while (itr.HasNext())
		{
			auto edge = (HalfEdge*)itr.Current();
			vec3 start = edge->Start()->Position();
			vec3 end = edge->End()->Position();
			vec3 centroid = edge->Face()->Centroid();

			start = (start - centroid) * 0.8f + centroid;
			end = (end - centroid) * 0.8f + centroid;

			position[counter] = start;
			position[counter + 1] = end;
			
			if (needColor)
			{
				color[counter] = vec3(1, 1, 1);
				color[counter + 1] = vec3(1, 1, 0);
			}

			counter += 2;

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