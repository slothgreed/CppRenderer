namespace KI
{
namespace Gfx
{
PolygonState::PolygonState()
{
	OffsetFill(true);
	Offset(1.0, 1.0);
}

PolygonState::~PolygonState()
{
}

void PolygonState::Bind()
{
	if (m_offsetFill)
	{
		glEnable(GL_POLYGON_OFFSET_FILL);
		glPolygonOffset(m_factor, m_units);
	}
	else
	{
		glDisable(GL_DEPTH_TEST);
	}

	Logger::GLError();
}

void PolygonState::UnBind()
{
	Logger::GLError();
}

bool PolygonState::Compare(const IGLState& state)
{
	return false;
}
}
}