namespace KI
{
namespace Renderer
{
GeometryPass::GeometryPass()
{
}

GeometryPass::~GeometryPass()
{
}

void GeometryPass::Initialize(int width, int height)
{
	m_pRenderTarget = make_shared<RenderTarget>();
	m_pRenderTarget->Initialize(4, width, height);
}

void GeometryPass::Resize(int width, int height)
{
	m_pRenderTarget->Resize(width, height);
}

void GeometryPass::Draw(const vector<shared_ptr<IModelNode>>& modelNodes)
{
	m_pRenderTarget->Begin();
	m_pRenderTarget->Clear();
	for (int i = 0; i < modelNodes.size(); i++)
	{
		modelNodes[i]->Draw();
	}

	m_pRenderTarget->End();
}
}
}