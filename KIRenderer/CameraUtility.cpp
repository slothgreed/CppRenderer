namespace KI
{
namespace Renderer
{
CameraUtility::CameraUtility()
{
}

CameraUtility::~CameraUtility()
{
}

void CameraUtility::CalcSceneRay(ICamera* pCamera, Viewport* pViewport, vec2 screenPos, vec3* near, vec3* far)
{
	*near = glm::unProject(
		vec3(screenPos.x, pViewport->Size().y - screenPos.y, 0),
		pCamera->ViewMatrix(),
		pCamera->Projection(),
		pViewport->GetScreen());

	*far = glm::unProject(
		vec3(screenPos.x, pViewport->Size().y - screenPos.y, 1),
		pCamera->ViewMatrix(),
		pCamera->Projection(),
		pViewport->GetScreen());
}
}
}