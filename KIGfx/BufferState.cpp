
namespace KI
{
namespace Gfx
{
BufferState::BufferState()
{
}

BufferState::~BufferState()
{
}

void BufferState::Bind()
{
	glClearColor(m_clearcolor.r, m_clearcolor.g, m_clearcolor.b, m_clearcolor.a);
	Logger::GLError();
}

void BufferState::UnBind()
{
	Logger::GLError();
}

bool BufferState::Compare(const IGLState& state)
{
	return false;
}
}
}