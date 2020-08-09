#ifndef GRAY_SCALE_EFFECT_H
#define GRAY_SCALE_EFFECT_H

namespace KI
{
namespace Asset
{
class DLL_EXPORT GrayScaleEffect : public IPostEffect
{
public:
	GrayScaleEffect();
	~GrayScaleEffect();

	virtual PFX_TYPE Type() { return PFX_TYPE::PFX_TYPE_GRAYSCALE; }
	virtual void Initialize(int width, int height) override;
	virtual void Draw(shared_ptr<UniformStruct> pUniform) override;
	void Resize(int width, int height) override;

	void SetTexture(shared_ptr<Texture> texture);
	shared_ptr<Texture> RenderTexture() { return m_pRenderTarget->ColorTexture(FRAMEBUFFER_COLOR_ATTACHMENT0); };

private:
	shared_ptr<GrayScaleShading> m_pShading;
	shared_ptr<RenderTarget> m_pRenderTarget;
	shared_ptr<RenderData> m_pPlane;
};
}
}

#endif GRAY_SCALE_EFFECT_H