#ifndef KI_IVIEW_H
#define KI_IVIEW_H

namespace KI
{
namespace RenderView
{
class DLL_EXPORT IView
{
public:
	IView() {};
	~IView() {};
	virtual bool Initialize() = 0;
	virtual bool Run() = 0;
	virtual void ProcessMouseEvent(const MouseInput& input) {};
	virtual void ProcessWindowEvent(const WindowEvent& winEvent) {};
private:
};
}
}

#endif