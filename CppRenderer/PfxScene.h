#ifndef PFX_SCENE_H
#define	PFX_SCENE_H

namespace KI
{

class PfxScene : public ViewViewModel
{
public:
	virtual ~PfxScene() {};
	virtual void Initialize() override;
	virtual void Invoke() override;
	virtual void ProcessMouseEvent(const MouseInput& input) override;
	virtual void WindowResize(int width, int height);
private:
	bool SetOutputTexture(int index);
	int MaxOutputTextureNum();
	void PreviewPfx();
	void NextPfx();
	shared_ptr<IRenderTarget> m_pBackTarget;
	shared_ptr<RenderTarget> m_pRenderTarget;
	shared_ptr<PfxPlane> m_pOutputPlane;
	shared_ptr<PfxRenderer> m_pPfxRenderer;
	shared_ptr<Scene> m_pScene;
	int m_CurrentIndex;
};
}


#endif // PFX_SCENE_H