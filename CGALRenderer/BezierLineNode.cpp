
namespace KI
{

BezierLineNode::BezierLineNode(shared_ptr<RenderData> pRenderData)
{
	m_pShading = make_shared<BezierLineShading>();
	m_pShading->SetPatchVertices(4);

	pRenderData->SetShading(m_pShading);
	m_pRenderData = pRenderData;
}

BezierLineNode::~BezierLineNode()
{
}

void BezierLineNode::DrawCore()
{
	m_pRenderData->Draw();
}

}
