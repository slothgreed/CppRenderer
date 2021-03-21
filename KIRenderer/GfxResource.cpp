
namespace KI
{
namespace Renderer
{
GfxResource::GfxResource()
{

}

GfxResource::~GfxResource()
{

}

void GfxResource::Initialize()
{
	m_pTextureManager = new TextureManager();
}

void GfxResource::Dispose()
{
	if (m_pTextureManager) {
		m_pTextureManager->Dispose();
		RELEASE_INSTANCE(m_pTextureManager);
	}
}
}
}