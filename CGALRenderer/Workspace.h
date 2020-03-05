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
	virtual void ShowProperty() override;
	virtual void ProcessMouseEvent(const MouseInput& input) override;
	virtual void AddModelNode(shared_ptr<IModelNode> pModelNode) override;

private:
	shared_ptr<Camera> m_pCamera; 
	std::shared_ptr<Mouse> m_pMouse;
	shared_ptr<IShader> m_pDefaultShader;
	shared_ptr<UniformScene> m_pUniformScene;
	shared_ptr<IRenderTarget> m_pBackTarget;
	vector<shared_ptr<IModelNode>> m_pRenderList;
	shared_ptr<RenderTarget> m_pRenderTarget;
	shared_ptr<PfxPlane> m_pOutputPlane;
	shared_ptr<PfxRenderer> m_pPfxRenderer;
	unique_ptr<CommandManager> m_pCommandManager;
};
}
#endif WORKSPACE_H