
namespace KI
{
namespace Renderer
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
	for (int i = 0; i < m_pPfxLists.size(); i++)
	{
		if (m_pPfxLists[i]->Apply())
		{
			m_pPfxLists[i]->Draw();
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

//void PfxRenderer::ReadFromXML(const boost::property_tree::ptree& tree)
//{
//	tree.find("PostEffect")->second.data();
//	for(auto item : tree)
//	{
//		for (auto &child : item.second.get_child("Effect"))
//		{
//			int type = child.second.get<int>("type");
//			shared_ptr<IPostEffect> pfx = nullptr;
//			if (type == PFX_TYPE::PFX_TYPE_GRAYSCALE)
//			{
//				pfx = make_shared<GrayScaleEffect>();
//			}
//			else if(type == PFX_TYPE::PFX_TYPE_SSLIC)
//			{
//				pfx = make_shared<SSLICEffect>();
//			}
//
//			pfx->ReadFromXML(child);
//			m_pPfxLists.push_back(pfx);
//		}
//	}
//}

//void PfxRenderer::WriteToXML(const boost::property_tree::ptree& tree)
//{
//	
//}

}
}