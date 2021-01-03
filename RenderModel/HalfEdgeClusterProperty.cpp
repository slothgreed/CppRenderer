namespace KI
{
namespace RenderModel
{
HalfEdgeClusterProperty::HalfEdgeClusterProperty()
{
}

void HalfEdgeClusterProperty::Build(IModelNode* pModelNode, IPropertyArgs* pPropertyArgs)
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

	HalfEdgeClusterPropertyArgs* pArgs = dynamic_cast<HalfEdgeClusterPropertyArgs*>(pPropertyArgs);
	if(pArgs == nullptr)
	{
		assert(0);
		return;
	}


	auto pRenderData = pModelNode->GetRenderData(0);
	auto pMeshBuffer = pRenderData->GetVertexBuffer();
	m_pRenderData = make_shared<RenderData>();
	vector<vec3> color;
	color.resize(pMeshBuffer->GetVertexSize());
	

	auto pVertexBuffer = make_shared<DefaultVertexBuffer>();
	pVertexBuffer->SetArrayBuffer(VERTEX_ATTRIB::VERTEX_ATTRIB_POSITION, pMeshBuffer->GetArrayBuffer(VERTEX_ATTRIB::VERTEX_ATTRIB_POSITION));
	pVertexBuffer->SetColor(color);
	m_pRenderData->SetGeometryData(PRIM_TYPE_LINES, pVertexBuffer, pRenderData->GetIndexBuffer());
	m_pRenderData->SetShading(make_shared<VertexShading>(VERTEX_SHADING_COLOR));

}

void HalfEdgeClusterProperty::Update(IModelNode* pModelNode, IPropertyArgs* pPropertyArgs)
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

void HalfEdgeClusterProperty::GetVBOData(HalfEdgeDS* model, vector<vec3>& position, vector<vec3>& color, bool needColor)
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

void HalfEdgeClusterProperty::Draw(shared_ptr<UniformStruct> pUniform)
{
	m_pRenderData->Draw(pUniform);
}

}
}