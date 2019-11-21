#ifndef CGAL_RENDERER_H
#define CGAL_RENDERER_H
namespace KI
{
class ShaderManager;
class Workspace;
class Mouse;
class MouseInput;
class WindowEvent;
class Viewport;
class CGALRenderer
{
public:
	CGALRenderer();
	~CGALRenderer();
	bool Initialize();
	void SetWorkspace(std::shared_ptr<Workspace> pWorkspace);
	bool Run();
	void ProcessMouseEvent(const MouseInput& input);
	void ProcessWindowEvent(const WindowEvent& winEvent);
private:
	CONTROLER_TYPE m_CurrentController;
	std::map<CONTROLER_TYPE,IController*> m_pController;
	GLFWwindow* m_window;
	std::shared_ptr<Workspace> m_pWorkspace;
	std::shared_ptr<Viewport> m_pViewport;
	std::shared_ptr<Mouse> m_pMouse;
};

static CGALRenderer* TheApp();

}

#endif CGAL_RENDERER_H
