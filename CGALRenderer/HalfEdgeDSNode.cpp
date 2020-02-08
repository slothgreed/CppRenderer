namespace KI
{
HalfEdgeDSNode::HalfEdgeDSNode(shared_ptr<HalfEdgeModel> model)
	:ModelNode(static_pointer_cast<IModel>(model))
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

}