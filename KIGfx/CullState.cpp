
namespace KI
{
namespace Gfx
{
CullState::CullState()
{
	CullEnable(false);
	FrontFace(FRONT_FACE_CCW);
	CullFace(CULL_MODE_BACK);
}

CullState::~CullState()
{
}

void CullState::Bind()
{
	if (m_cullFace)
	{
		glEnable(GL_CULL_FACE);
		glFrontFace(m_frontFace);
		glCullFace(m_cullMode);
	}
	else
	{
		glDisable(GL_CULL_FACE);
	}
	Logger::GLError();

}

void CullState::UnBind()
{
	// NotSupported:
	//glLineWidth(1.0f);

	Logger::GLError();

}

bool CullState::Compare(const IGLState& state)
{
	return false;
}
}
}