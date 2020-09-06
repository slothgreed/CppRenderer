namespace KI
{
namespace RenderView
{

class DLL_EXPORT ViewViewModel
{
public:
	ViewViewModel();
	~ViewViewModel();
	virtual void Invoke() = 0;
	virtual void ShowProperty() {};
	virtual void ProcessMouseEvent(const MouseInput& input) {};
	virtual void WindowResize(int width, int height) {};
	virtual void SetViewport(shared_ptr<Viewport> pViewport) { m_pViewport = pViewport; }
	shared_ptr<Viewport> GetViewport() { return m_pViewport; }
private:
	shared_ptr<Viewport> m_pViewport;
};



}
}