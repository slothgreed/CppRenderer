#ifndef BUNNY_SCENE_H
#define	BUNNY_SCENE_H

namespace KI
{

class BunnyScene : public ViewViewModel
{
public:
	virtual ~BunnyScene();
	virtual void Initialize() override;
	virtual void Invoke() override;
	virtual void ProcessMouseEvent(const MouseInput& input) override;
private:
	shared_ptr<GeometryPath> m_pGeometryPath;
	shared_ptr<IRenderTarget> m_pBackTarget;
	shared_ptr<Scene> m_pScene;
};
}
#endif // BUNNY_SCENE_H