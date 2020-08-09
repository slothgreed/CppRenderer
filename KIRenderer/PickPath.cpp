namespace KI
{
namespace Renderer
{

PickPath::PickPath()
{
}

PickPath::~PickPath()
{

}

void PickPath::Initialize(int width, int height)
{
	auto pBuildInfo = make_shared<IShaderBuildInfo>();
	pBuildInfo->SetShaderChunk(make_shared<BasicShading>(vec4(0, 0, 0, 1)));
	pBuildInfo->SetVertexBuffer(nullptr);
	m_pPickShader = ShaderManager::Instance()->FindOrNew(pBuildInfo);
	m_pRenderTarget = make_shared<RenderTarget>();
	m_pRenderTarget->Initialize(1, width, height);
}

void PickPath::Resize(int width, int height)
{
	m_pRenderTarget->Resize(width, height);
}

void PickPath::ResetPickID(vector<shared_ptr<IGLPick>>& modelNodes)
{
	for (int i = 0; i < modelNodes.size(); i++)
	{
		modelNodes[i]->AddPickID(i);
	}
}

void PickPath::Draw(shared_ptr<Scene> pScene)
{
	if (m_pPickShader == nullptr)
	{
		auto pBuildInfo = make_shared<IShaderBuildInfo>();
		pBuildInfo->SetShaderChunk(make_shared<PickShading>());
		m_pPickShader = ShaderManager::Instance()->FindOrNew(pBuildInfo);
	}


	m_pRenderTarget->Begin();
	m_pRenderTarget->Clear();
	m_pPickShader->Use();
	pScene->Bind();
	pScene->PickDraw(m_pPickShader);
	m_pPickShader->UnUse();
	pScene->UnBind();
	
	m_pRenderTarget->End();
}
}
}