#ifndef ALGORITHM_SCENE_H
#define ALGORITHM_SCENE_H

namespace KI
{

class AlgorithmScene : public ViewViewModel
{
public:
	AlgorithmScene();
	virtual ~AlgorithmScene();
	virtual void Initialize() override;
	virtual void ShowUI(ImGuiContext* context) override;
	virtual void Invoke() override;
	virtual void ProcessMouseEvent(const MouseInput& input) override;

private:
	shared_ptr<IRenderTarget> m_pBackTarget;
	shared_ptr<Scene> m_pScene;
	shared_ptr<HalfEdgeDSNode> m_pTargetNode;
	int m_level;
};

}



#endif ALGORITHM_SCENE_H