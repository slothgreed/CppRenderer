namespace KI
{
namespace Gfx
{
DepthState::DepthState()
{
	m_depthTest = false;
}

DepthState::~DepthState()
{
}

void DepthState::DepthTest(bool value)
{
	m_depthTest = value;
}
void DepthState::DepthFunc(COMP_FUNC func)
{
	m_depthFunc = func;
}
void DepthState::Bind()
{
	if (m_depthTest)
	{
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(m_depthFunc);
	}
	else
	{
		glDisable(GL_DEPTH_TEST);
	}

	Logger::GLError();
}

void DepthState::UnBind()
{
	Logger::GLError();
}

bool DepthState::Compare(const IGLState& state)
{
	return false;
}
}
}