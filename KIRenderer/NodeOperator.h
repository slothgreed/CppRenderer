#ifndef NODE_OPERATOR_H
#define NODE_OPERATOR_H

namespace KI
{
namespace Renderer
{

class IModelNode;
class DLL_EXPORT NodeOperator
{
public:
	NodeOperator();
	~NodeOperator();

	static void Rotate(IModelNode* pNode, const vec3& axis, float degree);
	static void Translate(IModelNode* pNode, const vec3& value);
	static void Scale(IModelNode* pNode, const vec3& value);
private:

};
}
}
#endif NODE_OPERATOR_H
