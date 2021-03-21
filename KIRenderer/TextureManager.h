#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

namespace KI
{
namespace Renderer
{
class DLL_EXPORT TextureManager
{
public: 
	TextureManager();
	~TextureManager();

	shared_ptr<Texture> Create();
	bool Dispose();
private:
	std::vector<shared_ptr<Texture>> m_pTexture;
};
};
}
#endif // !TEXTURE_FACTORY_H