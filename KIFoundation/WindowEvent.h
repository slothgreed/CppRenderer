#ifndef WINDOW_EVENT_H
#define WINDOW_EVENT_H
namespace KI
{
namespace Foundation
{
class DLL_EXPORT WindowEvent
{
public:
	WindowEvent() {};
	~WindowEvent() {};

	void SetEvent(WINDOW_EVENT windowEvent) { m_event = windowEvent; }
	WINDOW_EVENT Event() { return m_event; }
	void SetSize(int x, int y) { m_size.x = x; m_size.y = y; }
	const glm::ivec2&  Size() const { return m_size; } 
private:
	WINDOW_EVENT m_event;
	glm::ivec2 m_size;
};
}
}

#endif WINDOW_EVENT_H