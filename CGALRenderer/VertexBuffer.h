#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

enum VERTEX_ATTRIB
{
	VERTEX_ATTRIB_POSITION = 0,
	VERTEX_ATTRIB_NORMAL = 1,
	VERTEX_ATTRIB_COLOR = 2,
	VERTEX_ATTRIB_TEXCOORD = 3,
	VERTEX_ATTRIB_NUM = 4
};

// Point Normal Color Texcoord ˆÈŠO‚Í•ÊƒNƒ‰ƒX‚ÅŽÀ‘•
enum VERTEX_LAYOUT
{
	VERTEX_LAYOUT_P,	// Point
	VERTEX_LAYOUT_PN,	// Point Normal
	VERTEX_LAYOUT_PC,	// Point Color
	VERTEX_LAYOUT_PNC,	// Point Normal Color
	VERTEX_LAYOUT_PNCT,	// Point Normal Color Texcoord
	VERTEX_LAYOUT_NUM,	
};

class IVertexBuffer
{
public:
	IVertexBuffer() {};
	~IVertexBuffer() {};

	virtual void Draw() = 0;
private:

};

class VertexBuffer : IVertexBuffer
{
public:
	VertexBuffer();
	~VertexBuffer();
	void Generate(VERTEX_LAYOUT layout);
	void SetPosition(GLuint primitiveTypem, const std::vector<glm::vec3>& position);
	void SetNormal(const std::vector<glm::vec3>& normal);
	void SetColor(const std::vector<glm::vec3>& color);
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


#endif VERTEX_BUFFER_H
