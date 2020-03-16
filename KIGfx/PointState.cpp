namespace KI
{
namespace Gfx
{
PointState::PointState(GLfloat pointSize, GLboolean depthTest)
{
	m_pointSize = pointSize;
	m_depthTest = depthTest;
}

PointState::~PointState()
{
}

void PointState::Bind()
{
	if (m_depthTest == false)
	{
		glDisable(GL_DEPTH_TEST);
	}
	glPointSize(m_pointSize);
}

void PointState::UnBind()
{
	glPointSize(1.0f);
	if (m_depthTest == false)
	{
		glEnable(GL_DEPTH_TEST);
	}
}
bool PointState::Compare(const IGLState& state)
{
	assert(0);
	// memcmpåüèÿ
	// DepthÇÃONOFF
	if (state.Type() == STATE_TYPE_POINT)
	{
		const PointState* point = dynamic_cast<const PointState*>(&state);
		if (GetPointSize() != point->GetPointSize())
		{
			return false;
		}
	}

	return true;
}
}
}