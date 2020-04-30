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
	virtual void Draw() override;
	void Resize(int width, int height) override;

	void SetTexture(shared_ptr<Texture> texture);
	shared_ptr<Texture> RenderTexture() { return m_pRenderTarget->ColorTexture(0); };
	//virtual void ReadFromXML(const boost::property_tree::ptree& tree);
	//virtual void WriteToXML(const boost::property_tree::ptree& tree);

private:
	shared_ptr<RenderTarget> m_pRenderTarget;
	shared_ptr<Texture> m_pTexture;
	shared_ptr<RenderData> m_pPlane;
};
}
}

#endif GRAY_SCALE_EFFECT_H