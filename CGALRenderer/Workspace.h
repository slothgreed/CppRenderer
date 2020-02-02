#ifndef WORKSPACE_H
#define WORKSPACE_H
namespace KI
{
class Camera;
class IShader;
class DefaultVertexBuffer;
class UniformScene;
class UniformBuffer;
class CGALModelNode;
class CommandManager;
class Workspace : public IWorkspace
{
public:
	Workspace();
	~Workspace();
	virtual void Initialize(Project* m_pProject) override;
	virtual void Invoke() override;
	virtual void ShowProperty() override;

private:

	shared_ptr<IShader> m_pDefaultShader;
	shared_ptr<UniformScene> m_pUniformScene;
	vector<shared_ptr<IModelNode>> m_pRenderList;
	shared_ptr<IRenderTarget> m_pBackTarget;
	shared_ptr<RenderTarget> m_pRenderTarget;
	shared_ptr<PfxPlane> m_pOutputPlane;
	shared_ptr<PfxRenderer> m_pPfxRenderer;
	unique_ptr<CommandManager> m_pCommandManager;
};
}
#endif WORKSPACE_H