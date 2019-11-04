#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

enum VERTEX_ATTRIB
{
	VERTEX_ATTRIB_POSITION = 0,
	VERTEX_ATTRIB_NORMAL = 1,
	VERTEX_ATTRIB_COLOR = 3,
	VERTEX_ATTRIB_TEXCOORD = 4,
	VERTEX_ATTRIB_NUM = 5
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
	VertexBuffer(VERTEX_LAYOUT layout);
	~VertexBuffer();
	void Generate();
	void GenerateVAO();
	void SetPosition(GLuint primitiveTypem, const std::vector<glm::vec3>& position);
	void SetNormal(const std::vector<glm::vec3>& position);
	void Dispose();
	bool HasNormal();
	bool HasColor();
	bool HasTexCoord();
	int NumVertexAttrib();
	virtual void Draw() override;

private:
	GLuint m_id[VERTEX_ATTRIB_NUM];
	GLuint m_vaoId;
	GLuint m_PrimitiveType;
	GLuint m_vertexNum;
	VERTEX_LAYOUT m_layout;
	bool elements;
};


#endif VERTEX_BUFFER_H
