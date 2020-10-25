#ifndef CAMERA_CONTROLLER_H
#define CAMERA_CONTROLLER_H
namespace KI
{
namespace Logic
{
class DLL_EXPORT CameraControllerArgs : public IControllerArgs
{
public:

	friend class CameraController;

	CameraControllerArgs( std::shared_ptr<ICamera> camera) {
		m_pCamera = camera;
	};

	~CameraControllerArgs() {};

private:
	std::shared_ptr<ICamera> m_pCamera;
};

class DLL_EXPORT CameraController : public IController
{
public:
	CameraController(shared_ptr<CameraControllerArgs> pArgs);
	~CameraController();
	virtual void SetArgs(shared_ptr<IControllerArgs> pArgs) override;
	virtual bool Move(const Mouse& mouse) override;
	virtual bool Wheel(const Mouse&  mouse) override;
private:
	void Zoom(float ratio);
	void Rotate(vec2 move);
	void Translate(vec2 move);

	std::shared_ptr<CameraControllerArgs> m_pArgs;

	float m_ZoomRatio;
};
}
}
#endif CAMERA_CONTROLLER_H