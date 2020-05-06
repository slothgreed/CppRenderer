
namespace KI
{

BezierLineNode::BezierLineNode(shared_ptr<RenderData> pRenderData)
{
	auto pBuildInfo = make_shared<IShaderBuildInfo>(SHADER_TYPE_BEZIERLINE);
	pBuildInfo->SetVertexCode(make_shared<DefaultVertexCode>());
	pBuildInfo->SetTESCode(make_shared<BezierLineTESCode>());
	pBuildInfo->SetTCSCode(make_shared<BezierLineTCSCode>());
	pBuildInfo->SetFragCode(make_shared<DefaultFragCode>());
	auto pBezierShader = static_pointer_cast<BezierLineShader>(ShaderManager::Instance()->FindOrNew(pBuildInfo));
	pBezierShader->SetPatchVertices(4);

	auto pTCSUniform = make_shared<BezierLineUniform>();
	auto pMaterial = make_shared<GeneralPass>();
	pMaterial->SetShader(pBezierShader);
	pMaterial->GetUniform()->Set(nullptr, nullptr, pTCSUniform, nullptr, nullptr);
	pRenderData->SetMaterial(pMaterial);
	m_pRenderData = pRenderData;
}

BezierLineNode::~BezierLineNode()
{
}

void BezierLineNode::Draw()
{
	m_pRenderData->Draw();
}

}
