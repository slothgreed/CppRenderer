#ifndef RENDER_VIEW_H
#define RENDER_VIEW_H

namespace KI
{
namespace RenderView
{

class DLL_EXPORT OpenGLView
{
public:
	OpenGLView();
	~OpenGLView();
	bool Initialize();
	void SetViewModel(std::shared_ptr<ViewViewModel> pWorkspace);
	bool Run();
	void ProcessMouseEvent(const MouseInput& input);
	void ProcessWindowEvent(const WindowEvent& winEvent);
private:

	GLFWwindow* m_window;
	shared_ptr<ViewViewModel> m_pViewModel;
	shared_ptr<Viewport> m_pViewport;

};

static OpenGLView* TheApp();


}
}

#endif RENDER_VIEW_H
