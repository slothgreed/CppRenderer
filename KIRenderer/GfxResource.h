#ifndef GFX_RESOURCE_H
#define GFX_RESOURCE_H

namespace KI
{
namespace Renderer
{

class DLL_EXPORT GfxResource
{
public:
	GfxResource();
	~GfxResource();

	TextureManager* Textures() { return m_pTextureManager; }

	void Initialize();
	void Dispose();
private:


	TextureManager* m_pTextureManager;
};
}
}
#endif // !GFX_RESOURCE_H
