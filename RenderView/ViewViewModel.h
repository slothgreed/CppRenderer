namespace KI
{
namespace RenderView
{

class DLL_EXPORT ViewViewModel
{
public:
	ViewViewModel();
	~ViewViewModel();
	virtual void Initialize() {};
	virtual void ShowProperty() {};
	virtual void ProcessMouseEvent(const MouseInput& input) {};
	virtual void WindowResize(int width, int height) {};
	virtual void Invoke() {};
	virtual void SetViewport(shared_ptr<Viewport> pViewport) { m_pViewport = pViewport; }
	shared_ptr<Viewport> GetViewport() { return m_pViewport; }
	void SetController(CONTROLER_TYPE type, IController* value); 
protected:
	shared_ptr<Mouse> m_pMouse;
	CONTROLER_TYPE m_CurrentController;
	unique_ptr<CommandManager> m_pCommandManager;
	map<CONTROLER_TYPE, IController*> m_pController;

private:
	shared_ptr<Viewport> m_pViewport;
};



}
}