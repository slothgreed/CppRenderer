#ifndef MOUSE_H
#define MOUSE_H

class MouseInput;
class Mouse
{
public:
	Mouse();
	~Mouse();

	const glm::vec2& Position() const { return m_current; };
	const glm::vec2& Delta() const { return m_delta; };
	MOUSE_EVENT Event() const { return m_event; };
	MOUSE_BUTTON Button() const { return m_press; };
	int Wheel() const { return m_wheel; };
	bool Press(MOUSE_BUTTON value) const { return m_press & value; }
	void ApplyMouseInput(const MouseInput& input);
private:

	glm::vec2 m_before;
	glm::vec2 m_current;
	glm::vec2 m_delta;
	bool m_drag;
	MOUSE_EVENT m_event;
	MOUSE_BUTTON m_press;
	int m_wheel;
};

#endif MOUSE_H