#ifndef SSLIC_EFFECT_H
#define SSLIC_EFFECT_H

namespace KI
{
namespace Asset
{
class DLL_EXPORT SSLICEffect : public IPostEffect
{
public:
	SSLICEffect();
	~SSLICEffect();
	
	virtual PFX_TYPE Type() { return PFX_TYPE::PFX_TYPE_SSLIC; }
	virtual void Initialize(int width, int height) override;
	virtual void Draw(shared_ptr<IUniformStorage> pUniform) override;
	virtual void Resize(int width, int height) override;
	void SetRenderData(shared_ptr<RenderData> pRenderData);

private:
	shared_ptr<Texture> m_pNoizeTexture;
	shared_ptr<Texture> m_pBlendTexture;
	shared_ptr<RenderData> m_pModelData;
	shared_ptr<RenderData> m_pPlaneData;
	shared_ptr<RenderTarget> m_pRenderTarget;

	shared_ptr<BasicShading> m_pBasicShading;
};
}
}
#endif SSLIC_EFFECT_H