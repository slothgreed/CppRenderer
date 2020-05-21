#ifndef PFX_PLANE_H
#define PFX_PLANE_H

namespace KI
{
namespace Renderer
{
class DLL_EXPORT PfxPlane
{
public:
	PfxPlane(shared_ptr<IMaterial> pMaterial);
	~PfxPlane();
	void Initialize();
	void Draw();
private:
	shared_ptr<IMaterial> m_pMaterial;
	shared_ptr<RenderData> m_pRenderData;
};
}
}
#endif PFX_PLANE_H