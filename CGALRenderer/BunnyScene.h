#ifndef BUNNY_SCENE_H
#define	BUNNY_SCENE_H

namespace KI
{

class BunnyScene : public IWorkspace
{
public:
	virtual ~BunnyScene();
	virtual void Initialize(Project* m_pProejct) override;
	virtual void Invoke() override;
	virtual void ShowProperty() override;
	virtual void ProcessMouseEvent(const MouseInput& input) override;
	virtual void AddModelNode(shared_ptr<IModelNode> pModelNode) override;
private:
	shared_ptr<GeometryPass> m_pGeometryPass;
	vector<shared_ptr<IModelNode>> m_pRenderList;
	shared_ptr<IRenderTarget> m_pBackTarget;
	shared_ptr<Scene> m_pScene;
};
}
#endif // BUNNY_SCENE_H