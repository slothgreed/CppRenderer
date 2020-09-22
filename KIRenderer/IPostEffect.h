#ifndef IPFX_EFFECT_H
#define IPFX_EFFECT_H

namespace KI
{
namespace Renderer
{
enum PFX_TYPE
{
	PFX_TYPE_GRAYSCALE,
	PFX_TYPE_SSLIC,
};
class DLL_EXPORT IPostEffect : public IRenderPath
{
public:
	IPostEffect() : m_apply(true) {};
	~IPostEffect() {};

	virtual PFX_TYPE Type() = 0;
	virtual void Initialize(int width, int height) = 0;
	virtual void Resize(int width, int height) = 0;
	virtual void Draw(shared_ptr<UniformStruct> pUniform) = 0;
	virtual shared_ptr<Texture> RenderTexture(int index) = 0;
	virtual int RenderTextureNum() = 0;
	void SetApply(bool value) { m_apply = value; }
	bool Apply() { return m_apply; }

private:
	bool m_apply;

};
}
}
#endif IPFX_EFFECT_H