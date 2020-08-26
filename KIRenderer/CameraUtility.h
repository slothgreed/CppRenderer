#ifndef CAMERA_UTILITY_H
#define CAMERA_UTILITY_H
namespace KI
{
namespace Renderer
{

class DLL_EXPORT CameraUtility
{
public:
	CameraUtility();
	~CameraUtility();
	static void CalcSceneRay(ICamera* pCamera, 
		Viewport* pViewport, vec2 screenPos, vec3* near, vec3* far);

private:

};
}
}
#endif CAMERA_UTILITY_H