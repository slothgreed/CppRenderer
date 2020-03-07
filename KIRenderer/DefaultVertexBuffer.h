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
	void Generate(VERTEX_LAYOUT layout);
	void SetPosition(GLuint primitiveType, const std::vector<glm::vec3>& position);
	void SetNormal(const std::vector<glm::vec3>& normal);
	void SetColor(const std::vector<glm::vec3>& color);
	void SetTexcoord(const vector<vec2>& texcoord);
	void SetIndex(GLuint primitiveType, const std::vector<int>& index);
	void Dispose();

	GLuint PrimitiveType() { return m_PrimitiveType; }
	VERTEX_LAYOUT Layout() { return m_layout; };
	virtual void Draw() override;
	virtual string Type() { return DefaultVertexBufferTypeStr; }
	static string DefaultVertexBufferTypeStr;

	bool HasNormal();
	bool HasColor();
	bool HasTexCoord();
	bool HasIndex();

private:
	void GenerateVAO();
	int NumVertexAttrib();

	GLuint m_id[VERTEX_ATTRIB_NUM];
	GLuint m_vaoId;
	IndexBuffer m_indexBuffer;
	
	GLuint m_PrimitiveType;
	GLuint m_vertexNum;
	VERTEX_LAYOUT m_layout;
	bool elements;
};
}
}
#endif VERTEX_BUFFER_H
