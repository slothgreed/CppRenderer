#ifndef RENDERER_H
#define RENDERER_H

namespace KI
{
namespace Renderer
{
class DLL_EXPORT RenderSystem
{
public:
	RenderSystem();
	~RenderSystem();

	void Draw(shared_ptr<ICamera> pCamera);
private:
	
	vector<shared_ptr<IPostEffect>> m_pPfxLists;
};
}
}
#endif RENDERER_H