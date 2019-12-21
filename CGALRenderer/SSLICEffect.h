#ifndef SSLIC_EFFECT_H
#define SSLIC_EFFECT_H

namespace KI
{
class SSLICEffect : IPfxEffect
{
public:
	SSLICEffect();
	~SSLICEffect();

	virtual void Initialize() override;
	virtual void Draw() override;
	virtual void Resize(int width, int height) override;
	void SetDrawModel(shared_ptr<DefaultVertexBuffer> model);

private:
	shared_ptr<Texture> m_pNoizeTexture;
	shared_ptr<Texture> m_pBlendTexture;
	shared_ptr<SSLICShader> m_pSSLICShader;
	shared_ptr<DefaultShader> m_pModelShader;
	shared_ptr<DefaultVertexBuffer> m_pModel;
	shared_ptr<DefaultVertexBuffer> m_pPlaneBuffer;
	shared_ptr<RenderTarget> m_pRenderTarget;
};
}


#endif SSLIC_EFFECT_H