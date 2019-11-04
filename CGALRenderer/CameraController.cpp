CameraController::CameraController()
{
	m_ZoomRatio = 1.0f;
}

CameraController::~CameraController()
{
}

void CameraController::SetArgs(shared_ptr<IControllerArgs> pArgs)
{
	m_pArgs = static_pointer_cast<CameraControllerArgs>(pArgs);
}
bool CameraController::Move(const Mouse& mouse)
{
	if (mouse.Press(MOUSE_BUTTON::MOUSE_BUTTON_LEFT))
	{
		Camera* pCamera = m_pArgs->GetCamera().get();
		vec2 move = mouse.Delta();
		move.x *= 0.3;
		move.y *= -0.3;

		pCamera->MoveWithSpherical(move);
	}

	return true;
}

bool CameraController::Wheel(const Mouse&  mouse)
{
	if (mouse.Wheel() > 0)
	{
		Zoom(1 + 0.1f * m_ZoomRatio);
	}
	else
	{
		Zoom(1 - 0.1f * m_ZoomRatio);
	}

	return true;
}

void CameraController::Zoom(float ratio)
{
	Camera* pCamera = m_pArgs->GetCamera().get();
	vec3 eyeDirect = pCamera->Eye() - pCamera->Center();
	float len = glm::length(eyeDirect);
	
	len *= ratio;

	vec3 newEye = glm::normalize(eyeDirect) * len;

	pCamera->LookAt(newEye, pCamera->Center(), pCamera->Up());
}

void CameraController::Rotate(vec2 move)
{

}

void CameraController::Translate(vec2 move)
{
}