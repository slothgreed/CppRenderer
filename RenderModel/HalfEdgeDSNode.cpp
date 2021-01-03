namespace KI
{
namespace RenderModel
{
HalfEdgeDSNode::HalfEdgeDSNode(shared_ptr<HalfEdgeModel> model)
	:PolygonModelNode(static_pointer_cast<IModel>(model))
{
	VisibleHalfEdgeLine(true);
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
	}
	else
	{
		AddProperty(make_shared<HalfEdgeClusterProperty>(level));
	}
}
}
}