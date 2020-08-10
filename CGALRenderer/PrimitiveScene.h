#ifndef PRIMITIVE_SCENE_H
#define	PRIMITIVE_SCENE_H

namespace KI
{
class PrimitiveScene : public IWorkspace
{
public:
	virtual ~PrimitiveScene();
	virtual void Initialize(Project* m_pProejct) override;
	virtual void Invoke() override;
	virtual void ProcessMouseEvent(const MouseInput& input) override;
private:
	void NextModel();
	void PreviewModel();
	void ShowPrimitive(int index);
	shared_ptr<IRenderTarget> m_pBackTarget;
	shared_ptr<Scene> m_pScene;
	int m_currentPrimitive;
	shared_ptr<PickPath> m_pPickPath;
	shared_ptr<RenderData> m_pPlane;
	shared_ptr<OutputPath> m_pOutputPath;
};
}
#endif // PRIMITIVE_SCENE_H