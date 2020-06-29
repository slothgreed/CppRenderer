namespace KI
{
namespace Renderer
{

PickPath::PickPath()
{
	// 頂点情報を GL_TRIANGLES 用に作成しなおす必要があるため、利用しない。
	assert(0);
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

void PickPath::ResetPickID(const vector<shared_ptr<IModelNode>> modelNodes)
{
	//int startIndex = 0;
	//int nextStartIndex = 0;
	//for (int i = 0; i < modelNodes.size(); i++)
	//{
	//	modelNodes[i]->CalculatePickID(startIndex, nextStartIndex);
	//	startIndex = nextStartIndex;
	//}
}

void PickPath::Draw(const vector<shared_ptr<IModelNode>>& modelNodes)
{
	//m_pRenderTarget->Begin();
	//m_pRenderTarget->Clear();
	//m_pPickShader->Use();
	//for (int i = 0; i < modelNodes.size(); i++)
	//{
	//	modelNodes[i]->PickDraw();
	//}
	//m_pPickShader->UnUse();
	//m_pRenderTarget->End();
}
}
}