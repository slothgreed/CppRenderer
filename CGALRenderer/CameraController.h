#ifndef CAMERA_CONTROLLER_H
#define CAMERA_CONTROLLER_H
namespace KI
{
class Mouse;
class Camera;
class Viewport;
class CameraControllerArgs : public IControllerArgs
{
public:

	friend class CameraController;

	CameraControllerArgs(std::shared_ptr<Viewport> viewport, std::shared_ptr<Camera> camera) {
		m_pViewport = viewport;
		m_pCamera = camera;
	};

	~CameraControllerArgs() {};

private:
	std::shared_ptr<Viewport> m_pViewport;
	std::shared_ptr<Camera> m_pCamera;
};

class CameraController : public IController
{
public:
	CameraController();
	~CameraController();
	virtual void SetArgs(std::shared_ptr<IControllerArgs> m_pArgs) override;
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
#endif CAMERA_CONTROLLER_H