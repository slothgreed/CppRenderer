
namespace KI
{
namespace RenderModel
{
BezierLineNode::BezierLineNode(shared_ptr<RenderData> pRenderData)
{
	m_pShading = make_shared<BezierLineShading>();
	m_pShading->SetPatchVertices(4);

	pRenderData->SetShading(m_pShading);
	SetRenderData(pRenderData);
}

BezierLineNode::~BezierLineNode()
{
}

}
}
