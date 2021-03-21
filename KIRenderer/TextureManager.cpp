namespace KI
{
namespace Renderer
{
TextureManager::TextureManager()
{

}

TextureManager::~TextureManager()
{

}

shared_ptr<Texture> TextureManager::Create()
{
	auto pTexture = make_shared<Texture>();

	m_pTexture.push_back(pTexture);

	return pTexture;
}

bool TextureManager::Dispose()
{
	for (size_t i = 0; i < m_pTexture.size(); i++)
	{
		assert(!m_pTexture[i].unique());
		m_pTexture[i]->Dispose();
	}

	m_pTexture.clear();
	return false;
}
}
}