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
	virtual SHADER_TYPE Type() { return SHADER_TYPE::SHADER_TYPE_DEFAULT; }
	virtual void BindAttribDivisor() override;
	virtual void UnBindAttribDivisor() override;

	void SetPosition(GLuint primitiveType, const vector<vec3>& position);
	void SetNormal(const vector<vec3>& normal);
	void SetColor(const vector<vec3>& color);
	void SetTexcoord(const vector<vec2>& texcoord);
	void SetTranslate(const vector<vec3>& translate);
	GLuint Layout();

	bool HasAttribute(VERTEX_ATTRIB attribute);

private:
};
}
}
#endif VERTEX_BUFFER_H
