namespace KI
{
namespace RenderModel
{
HalfEdgeDSNode::HalfEdgeDSNode(shared_ptr<HalfEdgeModel> model)
	:PolygonModelNode(static_pointer_cast<IModel>(model))
{
	//VisibleHalfEdgeLine(true);
	VisibleTangent(true);
	model->CalcDownSampling();
}

HalfEdgeDSNode::~HalfEdgeDSNode()
{
}

void HalfEdgeDSNode::VisibleHalfEdgeLine(bool visibility)
{
	AddProperty(make_shared<HalfEdgeProperty>());
}

void HalfEdgeDSNode::VisibleCluster(bool visibility, int level)
{
	if (HasProperty(PROPERTY_TYPE::PROPERTY_TYPE_HALFEDGE_CLUSTER))
	{
		m_pProperty->Update(this,&HalfEdgeResolutionPropertyArgs(level));
	}
	else
	{
		m_pProperty = make_shared<HalfEdgeResolutionProperty>();
		AddProperty(m_pProperty, &HalfEdgeResolutionPropertyArgs(level));
	}
}

void HalfEdgeDSNode::VisibleTangent(bool visibility)
{
	if (HasProperty(PROPERTY_TYPE::PROPERTY_TYPE_VERTEX_TANGENT))
	{
		m_pTangentProperty->Update(this, nullptr);
	}
	else
	{
		m_pTangentProperty = make_shared<VertexTangentProperty>();
		AddProperty(m_pTangentProperty, nullptr);
	}
}
}
}