#ifndef BEZIER_LINE_NODE_H
#define BEZIER_LINE_NODE_H

namespace KI
{
namespace RenderModel
{
class DLL_EXPORT BezierLineNode : public IModelNode
{
public:
	BezierLineNode(shared_ptr<RenderData> pVertexBuffer);
	~BezierLineNode();

private:
	virtual void DrawCore(shared_ptr<UniformStruct> pUniform) override;
	shared_ptr<BezierLineShading> m_pShading;
	shared_ptr<RenderData> m_pRenderData;
};
}
}

#endif BEZIER_LINE_NODE_H