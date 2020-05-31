#include "IModelNode.h"
namespace KI
{
namespace Renderer
{
NodeOperator::NodeOperator()
{
}

NodeOperator::~NodeOperator()
{
}

void NodeOperator::Rotate(IModelNode* pNode, const vec3& axis, float degree)
{

}

void NodeOperator::Translate(IModelNode* pNode, const vec3& value)
{
	auto newMatrix = glm::translate(pNode->GetModelMatrix(), value);
	pNode->SetModelMatrix(newMatrix);
}

void NodeOperator::Scale(IModelNode* pNode, const vec3& value)
{
	pNode->GetModelMatrix();
	auto newMatrix = glm::scale(pNode->GetModelMatrix(), value);
	pNode->SetModelMatrix(newMatrix);
}
}
}
