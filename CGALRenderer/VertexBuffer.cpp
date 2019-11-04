#include "VertexBuffer.h"
VertexBuffer::VertexBuffer(VERTEX_LAYOUT layout)
{
	for (int i = 0; i < VERTEX_ATTRIB_NUM; i++)
	{
		m_id[i] = 0;
	}

	m_vaoId = 0;
	m_layout = layout;
}

VertexBuffer::~VertexBuffer()
{
	Dispose();
}

void VertexBuffer::Generate()
{
	GLuint* attrib = new GLuint[NumVertexAttrib()];
	glGenBuffers(NumVertexAttrib(), attrib);

	if (m_layout == VERTEX_LAYOUT_P)
	{
		m_id[VERTEX_ATTRIB_POSITION]	= attrib[0];
	}
	else if(m_layout == VERTEX_LAYOUT_PN)
	{
		m_id[VERTEX_ATTRIB_POSITION]	= attrib[0];
		m_id[VERTEX_ATTRIB_NORMAL]		= attrib[1];
	}
	else if (m_layout == VERTEX_LAYOUT_PC)
	{
		m_id[VERTEX_ATTRIB_POSITION]	= attrib[0];
		m_id[VERTEX_ATTRIB_COLOR]		= attrib[1];
	}
	else if (m_layout == VERTEX_LAYOUT_PNC)
	{
		m_id[VERTEX_ATTRIB_POSITION]	= attrib[0];
		m_id[VERTEX_ATTRIB_NORMAL]		= attrib[1];
		m_id[VERTEX_ATTRIB_COLOR]		= attrib[2];
	}
	else if(m_layout == VERTEX_LAYOUT_PNCT)
	{
		m_id[VERTEX_ATTRIB_POSITION]	= attrib[0];
		m_id[VERTEX_ATTRIB_NORMAL]		= attrib[1];
		m_id[VERTEX_ATTRIB_COLOR]		= attrib[2];
		m_id[VERTEX_ATTRIB_TEXCOORD]	= attrib[3];
	}
	else
	{
		assert(0);
	}

	delete attrib;
	Logger::GLError();
}

void VertexBuffer::SetPosition(GLuint primitiveType, const vector<vec3>& position)
{
	m_PrimitiveType = primitiveType;
	glBindBuffer(GL_ARRAY_BUFFER, m_id[VERTEX_ATTRIB_POSITION]);
	glBufferData(GL_ARRAY_BUFFER, position.size() * sizeof(vec3), position.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	m_vertexNum = position.size();
	Logger::GLError();
}

void VertexBuffer::SetNormal(const vector<vec3>& normal)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_id[VERTEX_ATTRIB_NORMAL]);
	glBufferData(GL_ARRAY_BUFFER, normal.size() * sizeof(vec3), normal.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::GenerateVAO()
{
	glGenVertexArrays(1, &m_vaoId);
	glBindVertexArray(m_vaoId);
	glEnableVertexAttribArray(VERTEX_ATTRIB_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, m_id[VERTEX_ATTRIB_POSITION]);
	glVertexAttribPointer(VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	if (HasNormal())
	{
		glEnableVertexAttribArray(VERTEX_ATTRIB_NORMAL);
		glBindBuffer(GL_ARRAY_BUFFER, m_id[VERTEX_ATTRIB_NORMAL]);
		glVertexAttribPointer(VERTEX_ATTRIB_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	}

	if (HasColor())
	{

	}

	if (HasTexCoord())
	{

	}

	glBindVertexArray(0);
	Logger::GLError();
}

void VertexBuffer::Dispose()
{
	if (m_id != 0)
	{
		glDeleteBuffers(VERTEX_ATTRIB_NUM, m_id);
	}

	if (m_vaoId != 0)
	{
		glDeleteVertexArrays(1, &m_vaoId);
	}
}

void VertexBuffer::Draw()
{
	glBindVertexArray(m_vaoId);
	glDrawArrays(m_PrimitiveType, 0, m_vertexNum);
	glBindVertexArray(0);
}

bool VertexBuffer::HasNormal()
{
	if (m_layout == VERTEX_LAYOUT_PN ||
		m_layout == VERTEX_LAYOUT_PNC ||
		m_layout == VERTEX_LAYOUT_PNCT)
	{
		return true;
	}

	return false;
}

bool VertexBuffer::HasColor()
{
	if (m_layout == VERTEX_LAYOUT_PC ||
		m_layout == VERTEX_LAYOUT_PNC ||
		m_layout == VERTEX_LAYOUT_PNCT)
	{
		return true;
	}

	return false;
}

bool VertexBuffer::HasTexCoord()
{
	if (m_layout == VERTEX_LAYOUT_PNCT)
	{
		return true;
	}

	return false;
}

int VertexBuffer::NumVertexAttrib()
{
	if (m_layout == VERTEX_LAYOUT_P)
	{
		return 1;
	}

	if (m_layout == VERTEX_LAYOUT_PC || 
		m_layout == VERTEX_LAYOUT_PN)
	{
		return 2;
	}

	if (m_layout == VERTEX_LAYOUT_PNC)
	{
		return 3;
	}

	if (m_layout == VERTEX_LAYOUT_PNCT)
	{
		return 4;
	}
}