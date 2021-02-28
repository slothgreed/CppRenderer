
namespace KI
{
namespace Asset
{

IHUD::IHUD()
{

}

IHUD::~IHUD()
{

}

void IHUD::SetWindowPosition(int top, int left)
{
	m_windowPosition = ivec2(top, left);
}
}
}