
namespace KI
{
namespace Renderer
{
OutputPath::OutputPath()
{
}

OutputPath::~OutputPath()
{
}

void OutputPath::Initialize(int width, int height)
{
	m_pBasicShading = make_shared<BasicShading>(BASIC_SHADING_TYPE::BASIC_SHADING_TYPE_TEXTURE);
}

void OutputPath::Resize(int width, int height)
{

}

void OutputPath::SetTexture(shared_ptr<Texture> pTexture)
{
	m_pBasicShading->SetTexture(pTexture);
}

void OutputPath::Draw(shared_ptr<IRenderTarget> pRenderTarget, shared_ptr<RenderData> pRenderData)
{
	if (m_pBasicShader == nullptr)
	{
		auto pBuildInfo = make_shared<IShaderBuildInfo>();
		pBuildInfo->SetVertexBuffer(pRenderData->GetVertexBuffer());
		pBuildInfo->SetShaderChunk(m_pBasicShading);
		m_pBasicShader = ShaderManager::Instance()->FindOrNew(pBuildInfo);
	}

	pRenderTarget->Begin();
	pRenderTarget->Clear();
	
	pRenderData->Draw(m_pBasicShader, m_pBasicShading, nullptr);

	pRenderTarget->End();
}
}
}
