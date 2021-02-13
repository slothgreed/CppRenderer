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
		return make_shared<HalfEdgeResolutionProperty>();
	case KI::RenderModel::PROPERTY_TYPE_BDB:
		return make_shared<BDBProperty>();
	case KI::RenderModel::PROPERTY_TYPE_VERTEX_TANGENT:
		return make_shared<VertexTangentProperty>();
	case KI::RenderModel::PROPERTY_TYPE_BVH:
		return make_shared<BVHProperty>();
	default:
		assert(0);
		break;
	}

	return nullptr;
}

void IRenderModelProperty::Build(IModelNode* pModelNode, IPropertyArgs* pPropertyArgs)
{
	BuildCore(pModelNode, pPropertyArgs);
	InitializeUI();
}

}
}