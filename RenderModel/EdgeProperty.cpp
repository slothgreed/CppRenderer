namespace KI
{
namespace RenderModel
{
EdgeProperty::EdgeProperty()
{
}

void EdgeProperty::BuildCore(IModelNode* pModelNode, IPropertyArgs* pPropertyArgs)
{
	shared_ptr<IPolygonModel> pModel;
	if (IPolygonModel::IsPolygonModel(pModelNode->GetModel()->Type()))
	{
		pModel = static_pointer_cast<IPolygonModel>(pModelNode->GetModel());
	}
	else
	{
		assert(0);
		return;
	}

	m_pRenderData = make_shared<RenderData>();
	
	vector<vec3> edge;
	pModel->GetEdgeList(edge);
	auto pEdgeBuffer = make_shared<DefaultVertexBuffer>();
	pEdgeBuffer->SetPosition(edge);
	
	m_pRenderData->SetGeometryData(PRIM_TYPE_LINES, pEdgeBuffer);
	m_pRenderData->SetShading(make_shared<BasicShading>(vec4(0, 0, 0, 1)));

}

void EdgeProperty::Update(IModelNode* pModelNode, IPropertyArgs* pPropertyArgs)
{
	
}


void EdgeProperty::Draw(shared_ptr<UniformStruct> pUniform)
{
	m_pRenderData->Draw(pUniform);
}

}
}