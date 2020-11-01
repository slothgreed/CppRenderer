namespace KI
{
namespace RenderModel
{
HalfEdgeProperty::HalfEdgeProperty()
{
}

void HalfEdgeProperty::Build(IModelNode* pModelNode)
{
	shared_ptr<HalfEdgeModel> pModel;
	if (pModelNode->GetModel()->Type() == MODEL_TYPE_HALF_EDGE)
	{
		pModel = static_pointer_cast<HalfEdgeModel>(pModelNode->GetModel());
	}
	else
	{
		assert(0);
		return;
	}

	m_pRenderData = make_shared<RenderData>();

	vector<vec3> position;
	vector<vec3> color;
	GetVBOData(pModel->GetHalfEdgeDS().get(), position, color, true);
	position.resize(pModel->GetHalfEdgeDS()->EdgeList().size() * 2);
	color.resize(pModel->GetHalfEdgeDS()->EdgeList().size() * 2);

	auto pVertexBuffer = make_shared<DefaultVertexBuffer>();
	pVertexBuffer->SetPosition(position);
	pVertexBuffer->SetColor(color);
	m_pRenderData->SetGeometryData(PRIM_TYPE_LINES, pVertexBuffer);
	m_pRenderData->SetShading(make_shared<BasicShading>(vec4(0, 0, 0, 1)));

}

void HalfEdgeProperty::Update(IModelNode* pModelNode)
{
	vector<vec3> position;
	vector<vec3> color;
	shared_ptr<HalfEdgeModel> pModel;
	if (pModelNode->GetModel()->Type() == MODEL_TYPE_HALF_EDGE)
	{
		pModel = static_pointer_cast<HalfEdgeModel>(pModelNode->GetModel());
	}
	else
	{
		assert(0);
		return;
	}

	GetVBOData(pModel->GetHalfEdgeDS().get(), position, color, false);

	auto pVertexBuffer = m_pRenderData->GetVertexBuffer();
	if (pVertexBuffer->Type() == VERTEX_BUFFER_TYPE_DEFAULT)
	{
		auto pDefaultBuffer = static_pointer_cast<DefaultVertexBuffer>(pVertexBuffer);
		pDefaultBuffer->SetPosition(position);
	}
	else
	{
		assert(0);
	}
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

void HalfEdgeProperty::Draw(shared_ptr<UniformStruct> pUniform)
{
	m_pRenderData->Draw(pUniform);
}

}
}