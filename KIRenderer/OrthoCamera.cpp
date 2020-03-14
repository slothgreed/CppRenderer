namespace KI
{
namespace Renderer
{

OrthoCamera::OrthoCamera()
{
}

OrthoCamera::~OrthoCamera()
{
}

void OrthoCamera::Ortho(float left, float right, float bottom, float top, float _near, float _far)
{
	m_Project = glm::ortho(left, right, bottom, top, _near, _far);
}

void OrthoCamera::FitToBDB(const BDB& bdb)
{

}
}
}
