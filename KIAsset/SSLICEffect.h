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
	virtual void Draw(shared_ptr<UniformStruct> pUniform) override;
	virtual void Resize(int width, int height) override;
	void SetModelNode(shared_ptr<IModelNode> pModelNode);
	virtual int RenderTextureNum() override { return 3; }
	virtual shared_ptr<Texture> RenderTexture(int index) override;

private:
	shared_ptr<Texture> m_pNoizeTexture;
	shared_ptr<Texture> m_pBlendTexture;
	shared_ptr<IModelNode> m_pModelNode;
	shared_ptr<RenderData> m_pPlaneData;
	shared_ptr<RenderTarget> m_pRenderTarget;

	shared_ptr<IShader> m_pBasicShader;
	shared_ptr<IShading> m_pBasicShading;
};
}
}
#endif SSLIC_EFFECT_H