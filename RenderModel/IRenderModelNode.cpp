namespace KI
{
namespace RenderModel
{

void IRenderModelNode::VisibleProperty(PROPERTY_TYPE type, bool visible)
{
	auto pProperty = GetProperty(type);
	
	if (visible)
	{
		if (pProperty == nullptr)
		{
			pProperty = IRenderModelProperty::Create(type);
			AddProperty(pProperty);
		}
		
		pProperty->SetVisible(visible);
	}
	else
	{
		if (pProperty)
			pProperty->SetVisible(visible);
	}
}
}
}