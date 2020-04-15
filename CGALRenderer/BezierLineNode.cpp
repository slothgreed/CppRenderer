
namespace KI
{

BezierLineNode::BezierLineNode(shared_ptr<RenderData> pRenderData)
{

	auto pBuildInfo = make_shared<IShaderBuildInfo>(SHADER_TYPE_BEZIERLINE);
	pBuildInfo->SetVertexCode(make_shared<DefaultVertexCode>());
	pBuildInfo->SetTESCode(make_shared<BezierLineTESCode>());
	pBuildInfo->SetTCSCode(make_shared<BezierLineTCSCode>());
	pBuildInfo->SetFragCode(make_shared<DefaultFragCode>());
	m_pBezierShader = static_pointer_cast<BezierLineShader>(ShaderManager::Instance()->FindOrNew(pBuildInfo));
	m_pBezierShader->SetPatchVertices(4);
	m_pRenderData = pRenderData;
	auto pTCSUniform = make_shared<BezierLineUniform>();
	m_pUniform = make_shared<UniformSet>(nullptr, nullptr, pTCSUniform, nullptr, nullptr);
}

BezierLineNode::~BezierLineNode()
{
}

void BezierLineNode::Draw()
{
	m_pBezierShader->Use();
	m_pBezierShader->Bind(m_pUniform);
	m_pRenderData->Draw();
	m_pBezierShader->UnBind(m_pUniform);
	m_pBezierShader->UnUse();
}

}
