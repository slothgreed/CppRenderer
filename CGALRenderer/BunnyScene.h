#ifndef BUNNY_SCENE_H
#define	BUNNY_SCENE_H

namespace KI
{

class BunnyScene : public IWorkspace
{
public:
	virtual ~BunnyScene() {};
	virtual void Initialize(Project* m_pProejct) override;
	virtual void Invoke() override;
	virtual void ShowProperty() override;

private:
	shared_ptr<IShader> m_pDefaultShader;
	shared_ptr<UniformScene> m_pUniformScene;
	vector<shared_ptr<IModelNode>> m_pRenderList;
	shared_ptr<IRenderTarget> m_pBackTarget;
	unique_ptr<CommandManager> m_pCommandManager;
};
}
#endif // BUNNY_SCENE_H