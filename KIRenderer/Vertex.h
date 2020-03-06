#ifndef VERTEX_H

namespace KI
{
namespace Renderer
{
class Vertex
{
public:
	Vertex(vec3 position, vec3 normal) { m_position = position, m_normal = normal; }
	void SetPosition(vec3 position) { m_position = position; }
	vec3 Position() { return m_position; };

	void SetColor(vec3 color) { m_color = color; }
	vec3 Color() { return m_color; }

	void SetNormal(vec3 normal) { m_normal = normal; }
	vec3 Normal() { return m_normal; }

	void SetTexcoord(vec3 texcoord) { m_texcoord = texcoord; }
	vec2 Texcoord(vec3 texcoord) { return m_texcoord; }
private:

	vec3 m_position;
	vec3 m_color;
	vec3 m_normal;
	vec3 m_texcoord;

};
}
}


#endif // !VERTEX_H
