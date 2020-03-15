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
	virtual void ProcessMouseEvent(const MouseInput& input) override;
private:
	shared_ptr<GeometryPass> m_pGeometryPass;
	shared_ptr<IRenderTarget> m_pBackTarget;
	shared_ptr<Scene> m_pScene;
};
}
#endif // BUNNY_SCENE_H