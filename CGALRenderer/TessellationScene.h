#ifndef TESSELLATION_SCENE
#define TESSELLATION_SCENE

namespace KI
{

class TessellationScene : public IWorkspace
{
public:
	TessellationScene();
	~TessellationScene();

	virtual void Initialize(Project* pProject) override;
	virtual void Invoke() override;
	virtual void ProcessMouseEvent(const MouseInput& input) override; 
private:
	shared_ptr<Scene> m_pScene;
	shared_ptr<BezierLineNode> m_pBezierNode;
	shared_ptr<IRenderTarget> m_pBackTarget;
};

}


#endif TESSELLATION_SCENE