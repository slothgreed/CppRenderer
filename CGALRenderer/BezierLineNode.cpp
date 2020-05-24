
namespace KI
{

BezierLineNode::BezierLineNode(shared_ptr<RenderData> pRenderData)
{
	m_pMaterial = make_shared<BezierLineMaterial>();
	m_pMaterial->SetPatchVertices(4);

	pRenderData->SetMaterial(m_pMaterial);
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
