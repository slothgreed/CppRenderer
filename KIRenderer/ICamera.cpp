namespace KI
{
namespace Renderer
{

ICamera::ICamera()
{
}

ICamera::~ICamera()
{
}

void ICamera::LookAt(const vec3& eye, const vec3& center, const vec3& up)
{
	m_View = glm::lookAt(eye, center, up);
	m_eye = eye;
	m_center = center;
	m_up = up;
	m_direction = glm::normalize(m_eye - m_center);
	m_distance = glm::length(m_eye - m_center);
}


}
}