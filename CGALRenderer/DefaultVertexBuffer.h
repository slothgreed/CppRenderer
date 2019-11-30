#ifndef DEFAULT_VERTEX_BUFFER_H
#define DEFAULT_VERTEX_BUFFER_H
namespace KI
{


class DefaultVertexBuffer : public IVertexBuffer
{
public:
	DefaultVertexBuffer();
	~DefaultVertexBuffer();
	void Generate(VERTEX_LAYOUT layout);
	void SetPosition(GLuint primitiveTypem, const std::vector<glm::vec3>& position);
	void SetNormal(const std::vector<glm::vec3>& normal);
	void SetColor(const std::vector<glm::vec3>& color);
	void SetTexcoord(const vector<vec2>& texcoord);
	void SetIndex(const std::vector<int>& index);
	void Dispose();
	VERTEX_LAYOUT Layout() { return m_layout; };
	virtual void Draw() override;

private:
	void GenerateVAO();
	bool HasNormal();
	bool HasColor();
	bool HasTexCoord();
	bool HasIndex();
	int NumVertexAttrib();

	GLuint m_id[VERTEX_ATTRIB_NUM];
	GLuint m_vaoId;
	GLuint m_indexId;
	GLuint m_indexSize;
	
	GLuint m_PrimitiveType;
	GLuint m_vertexNum;
	VERTEX_LAYOUT m_layout;
	bool elements;
};

}
#endif VERTEX_BUFFER_H
