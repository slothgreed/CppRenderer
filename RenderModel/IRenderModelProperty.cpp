namespace KI
{
namespace RenderModel
{

shared_ptr<IModelProperty> IRenderModelProperty::Create(PROPERTY_TYPE type)
{
	switch (type)
	{
	case KI::RenderModel::PROPERTY_TYPE_NORMAL:
		return make_shared<NormalProperty>();
	case KI::RenderModel::PROPERTY_TYPE_HALFEDGE:
		return make_shared<HalfEdgeProperty>();
	case KI::RenderModel::PROPERTY_TYPE_RESOLUTION:
		return make_shared<ResolutionParameterProperty>();
	case KI::RenderModel::PROPERTY_TYPE_BDB:
		return make_shared<BDBProperty>();
	case KI::RenderModel::PROPERTY_TYPE_BVH:
		return make_shared<BVHProperty>();
	case KI::RenderModel::PROPERTY_TYPE_VERTEX_INDEX:
		return make_shared<VertexIndexProperty>();
	case KI::RenderModel::PROPERTY_TYPE_EDGE:
		return make_shared<EdgeProperty>();
	default:
		assert(0);
		break;
	}

	return nullptr;
}

void IRenderModelProperty::Build(IModelNode* pModelNode, IPropertyArgs* pPropertyArgs)
{
	SetModelNode(pModelNode);
	BuildCore(pModelNode, pPropertyArgs);
	InitializeUI();
}

}
}