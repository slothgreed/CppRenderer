namespace KI
{
namespace RenderModel
{
HalfEdgeDSNode::HalfEdgeDSNode(shared_ptr<HalfEdgeModel> model)
	:PolygonModelNode(static_pointer_cast<IModel>(model))
{
	//VisibleHalfEdgeLine(true);
	model->CalcDownSampling();
	model->CalcBVH();
	VisibleTangent(true);
	VisibleBVH(true);
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
void HalfEdgeDSNode::VisibleBVH(bool visible)
{
	if (HasProperty(PROPERTY_TYPE::PROPERTY_TYPE_BVH))
	{
		m_pBVHProperty->Update(this, nullptr);
	}
	else
	{
		m_pBVHProperty = make_shared<BVHProperty>();
		AddProperty(m_pBVHProperty, nullptr);
	}
}
}
}