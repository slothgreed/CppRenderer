
namespace KI
{
namespace Gfx
{
LineState::LineState()
{
	m_lineWidth = 1.0f;
}

LineState::~LineState()
{
}

void LineState::Bind()
{
	// NotSupported: on opengl4.0
	//glLineWidth(m_lineWidth);
	Logger::GLError();

}

void LineState::UnBind()
{
	// NotSupported:
	//glLineWidth(1.0f);

	Logger::GLError();

}

bool LineState::Compare(const IGLState& state)
{
	if (state.Type() == STATE_TYPE_LINE)
	{
		const LineState* line = dynamic_cast<const LineState*>(&state);
		if (GetLineWidth() != line->GetLineWidth())
		{
			return false;
		}
	}

	return true;
}
}
}