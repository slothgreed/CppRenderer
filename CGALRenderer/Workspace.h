#ifndef WORKSPACE_H
#define WORKSPACE_H
namespace KI
{
class CGALModelNode;
class Workspace : public IWorkspace
{
public:
	Workspace();
	~Workspace();
	virtual void Initialize(Project* m_pProject) override;
	virtual void Invoke() override;
	virtual void ProcessMouseEvent(const MouseInput& input) override;

private:
	shared_ptr<IRenderTarget> m_pBackTarget;
	shared_ptr<RenderTarget> m_pRenderTarget;
	shared_ptr<PfxPlane> m_pOutputPlane;
	shared_ptr<PfxRenderer> m_pPfxRenderer;
	shared_ptr<Scene> m_pScene;
};
}
#endif WORKSPACE_H