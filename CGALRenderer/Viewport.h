#ifndef VIEWPORT_H
#define VIEWPORT_H

class Viewport
{
public:
	Viewport();
	~Viewport();
	void SetPosition(int x, int y);
	void Resize(int width, int height);
	void ConvertWindowToScreenCoordinate(const glm::vec2& position, glm::vec2& result);

	const glm::ivec2& const Position() { return m_position; }
	const glm::ivec2& const Size() { return m_size; }

private:
	glm::ivec2 m_position;
	glm::ivec2 m_size;
};

#endif VIEWPORT_H
