#ifndef PFX_PLANE_H
#define PFX_PLANE_H

namespace KI
{
namespace Renderer
{
class DLL_EXPORT PfxPlane
{
public:
	PfxPlane(shared_ptr<IShaderPass> pMaterial);
	~PfxPlane();
	void Initialize();
	void Draw();
private:
	shared_ptr<IShaderPass> m_pMaterial;
	shared_ptr<RenderData> m_pRenderData;
};
}
}
#endif PFX_PLANE_H