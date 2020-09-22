#ifndef PFX_PLANE_H
#define PFX_PLANE_H

namespace KI
{
namespace Asset
{
class DLL_EXPORT PfxPlane
{
public:
	PfxPlane();
	~PfxPlane();
	void Initialize();
	void Draw();
	void SetTexture(shared_ptr<Texture> pTexture);
private:
	shared_ptr<OutputShading> m_pShading;
	shared_ptr<RenderData> m_pRenderData;
};
}
}
#endif PFX_PLANE_H