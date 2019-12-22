
namespace KI
{

PfxRenderer::PfxRenderer()
{
}

PfxRenderer::~PfxRenderer()
{
}

void PfxRenderer::AddPostEffect(shared_ptr<IPostEffect> postEffect)
{
	m_pPfxLists.push_back(postEffect);
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
	for (int i = 0; i < m_pPfxLists.size(); i++)
	{
		if (m_pPfxLists[i]->Apply())
		{
			m_pPfxLists[i]->Draw();
		}
	}
}

}
