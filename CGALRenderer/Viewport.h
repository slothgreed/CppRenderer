#ifndef VIEWPORT_H
#define VIEWPORT_H
namespace KI
{
class Viewport
{
public:
	Viewport();
	~Viewport();
	void SetPosition(int x, int y);
	void Resize(int width, int height);
	void ConvertWindowToScreenCoordinate(const vec2& position, vec2& result);

	const ivec2 Position() const { return m_position; }
	const ivec2 Size()  const { return m_size; }
	const ivec4 GetScreen() const {	return vec4(m_position.x, m_position.y, m_size.x, m_size.y);}
private:
	ivec2 m_position;
	ivec2 m_size;
};
}
#endif VIEWPORT_H
