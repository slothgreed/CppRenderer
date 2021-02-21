#ifndef LOGIC_EVENT_ARGS_H
#define LOGIC_EVENT_ARGS_H

namespace KI
{
namespace RenderModel
{

enum RENDER_EVENT_ARGS_TYPE : unsigned int
{
	CAMERA_CHANGE_EVENT = 0,
	EVENT_ARGS_NUM = 1,
};

class DLL_EXPORT CameraChangeEventArgs : public IEventArgs
{
public:
	CameraChangeEventArgs(ICamera* pTarget) : m_pCamera(pTarget) {};
	~CameraChangeEventArgs() {};

	const ICamera* const GetCamera() { return m_pCamera; }
private:
	ICamera* m_pCamera;
};

}
}


#endif // !LOGIC_EVENT_ARGS_H
