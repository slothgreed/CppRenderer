#ifndef DEFAULT_VERTEX_BUFFER_H
#define DEFAULT_VERTEX_BUFFER_H
namespace KI
{
namespace Renderer
{
class DLL_EXPORT DefaultVertexBuffer : public IVertexBuffer
{
public:
	DefaultVertexBuffer();
	~DefaultVertexBuffer();
	void SetPosition(GLuint primitiveType, const std::vector<glm::vec3>& position);
	void SetNormal(const std::vector<glm::vec3>& normal);
	void SetColor(const std::vector<glm::vec3>& color);
	void SetTexcoord(const vector<vec2>& texcoord);

	GLuint Layout();
	virtual SHADER_TYPE Type() { return SHADER_TYPE::SHADER_TYPE_DEFAULT; }

	bool HasAttribute(VERTEX_ATTRIB attribute);

private:
};
}
}
#endif VERTEX_BUFFER_H
