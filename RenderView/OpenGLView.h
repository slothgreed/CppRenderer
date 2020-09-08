#ifndef RENDER_VIEW_H
#define RENDER_VIEW_H

namespace KI
{
namespace RenderView
{

class DLL_EXPORT OpenGLView : public IView
{
public:
	OpenGLView();
	~OpenGLView();
	virtual bool Initialize() override;
	void SetViewModel(std::shared_ptr<ViewViewModel> pWorkspace);
	virtual bool Run() override;
	virtual void ProcessMouseEvent(const MouseInput& input) override;
	virtual void ProcessWindowEvent(const WindowEvent& winEvent) override;
private:

	GLFWwindow* m_window;
	shared_ptr<ViewViewModel> m_pViewModel;
	shared_ptr<Viewport> m_pViewport;

};

static OpenGLView* TheApp();


}
}

#endif RENDER_VIEW_H
