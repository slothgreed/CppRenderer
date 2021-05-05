#ifndef RUNGE_KUTTA_SCENE
#define RUNGE_KUTTA_SCENE

namespace KI
{
class RungeKuttaScene : public ViewViewModel
{
public:
	RungeKuttaScene();
	~RungeKuttaScene();

public:
	virtual void Initialize() override;
	virtual void Invoke() override;
	virtual void ProcessMouseEvent(const MouseInput& input)override;

private:
	float m_time;
	float m_dt;
	void Update();
	void InitializePoint();
	shared_ptr<Scene> m_pScene;
	shared_ptr<PrimitiveNode> m_pPointNode;
	shared_ptr<IRenderTarget> m_pBackTarget;
	vector<vec3> m_position;
};
}


#endif RUNGE_KUTTA_SCENE