namespace KI
{
namespace Gfx
{
BlendState::BlendState()
{
	m_enable = false;
	m_Src = BLEND_FACTOR_ZERO;
	m_Dst = BLEND_FACTOR_ZERO;
}

BlendState::~BlendState()
{
}

void BlendState::Enable(bool value)
{
	m_enable = value;
}

void BlendState::BlendFunc(BLEND_FACTOR src, BLEND_FACTOR dst)
{
	m_Src = src;
	m_Dst = dst;
}

void BlendState::Bind()
{
	if (m_enable)
	{
		glEnable(GL_BLEND);
		glBlendFunc(m_Src, m_Dst);
	}
	else
	{
		glDisable(GL_BLEND);
	}

	Logger::GLError();
}

void BlendState::UnBind()
{
	if (m_enable)
	{
		glDisable(GL_BLEND);
	}
}

bool BlendState::Compare(const IGLState& state)
{
	return false;
}
}
}