#ifndef BEZIER_LINE_NODE_H
#define BEZIER_LINE_NODE_H

namespace KI
{
namespace RenderModel
{
class DLL_EXPORT BezierLineNode : public IRenderModelNode
{
public:
	BezierLineNode(shared_ptr<RenderData> pVertexBuffer);
	~BezierLineNode();

private:
	shared_ptr<BezierLineShading> m_pShading;
};
}
}

#endif BEZIER_LINE_NODE_H