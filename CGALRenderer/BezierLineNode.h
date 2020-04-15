#ifndef BEZIER_LINE_NODE_H
#define BEZIER_LINE_NODE_H

namespace KI
{

class BezierLineNode : public IModelNode
{
public:
	BezierLineNode(shared_ptr<RenderData> pVertexBuffer);
	~BezierLineNode();

	virtual void Draw();

private:
	shared_ptr<RenderData> m_pRenderData;
	shared_ptr<BezierLineShader> m_pBezierShader;
	shared_ptr<UniformSet> m_pUniform;
};
}

#endif BEZIER_LINE_NODE_H