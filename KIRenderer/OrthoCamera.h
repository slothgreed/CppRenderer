#ifndef ORTHO_CAMERA_H
#define	ORTHO_CAMERA_H

namespace KI
{
namespace Renderer
{

class DLL_EXPORT OrthoCamera : public ICamera
{
public:
	OrthoCamera();
	~OrthoCamera();
	CAMERA_TYPE Type() override { return CAMERA_TYPE::CAMERA_TYPE_PERSPECTIVE; };
	void Ortho(float left, float right, float bottom, float top, float _near, float _far);
	virtual void FitToBDB(const BDB& bdb) override;

private:
};

}
}
#endif // ORTHO_CAMERA_H