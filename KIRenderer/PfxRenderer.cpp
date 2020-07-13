
namespace KI
{
namespace Renderer
{
PfxRenderer::PfxRenderer()
{
	m_pUniformBuilder = make_unique<UniformBuilder>();
}

PfxRenderer::~PfxRenderer()
{
}

void PfxRenderer::AddPostEffect(shared_ptr<IPostEffect> postEffect)
{
	m_pPfxLists.push_back(postEffect);
}

IPostEffect* PfxRenderer::FindPostEffect(int index)
{
	if (m_pPfxLists.size() <= index)
	{
		assert(0);
		return nullptr;
	}

	return m_pPfxLists[index].get();
}

int PfxRenderer::PostEffectNum()
{
	return (int)m_pPfxLists.size();
}

IPostEffect* PfxRenderer::FindPostEffect(PFX_TYPE type)
{
	for (int i = 0; i < m_pPfxLists.size(); i++)
	{
		if (m_pPfxLists[i]->Type() == type)
		{
			return m_pPfxLists[i].get();
		}
	}

	return nullptr;
}

void PfxRenderer::Draw()
{
	auto pUniform = m_pUniformBuilder->BuildStruct();
	for (int i = 0; i < m_pPfxLists.size(); i++)
	{
		if (m_pPfxLists[i]->Apply())
		{
			m_pPfxLists[i]->Draw(pUniform);
		}
	}
}

void PfxRenderer::Resize(int width, int height)
{
	for (int i = 0; i < m_pPfxLists.size(); i++)
	{
		m_pPfxLists[i]->Resize(width, height);
	}
}

}
}