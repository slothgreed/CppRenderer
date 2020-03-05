#ifndef CGAL_RENDERER_H
#define CGAL_RENDERER_H
namespace KI
{
class Workspace;
class CGALRenderer
{
public:
	CGALRenderer();
	~CGALRenderer();
	bool Initialize();
	void SetWorkspace(std::shared_ptr<IWorkspace> pWorkspace);
	bool Run();
	void ProcessMouseEvent(const MouseInput& input);
	void ProcessWindowEvent(const WindowEvent& winEvent);
private:
	
	GLFWwindow* m_window;
	shared_ptr<IWorkspace> m_pWorkspace;
	shared_ptr<Viewport> m_pViewport;
};

static CGALRenderer* TheApp();

}

#endif CGAL_RENDERER_H
