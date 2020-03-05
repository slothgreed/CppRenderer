namespace KI
{
namespace Renderer
{
string DefaultVertexBuffer::DefaultVertexBufferTypeStr = "DEFAULT";
DefaultVertexBuffer::DefaultVertexBuffer()
{
	for (int i = 0; i < VERTEX_ATTRIB_NUM; i++)
	{
		m_id[i] = 0;
	}

	m_vaoId = 0;
	m_indexId = 0;
}

DefaultVertexBuffer::~DefaultVertexBuffer()
{
	Dispose();
}

void DefaultVertexBuffer::Generate(VERTEX_LAYOUT layout)
{
	m_layout = layout;
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
	else if (m_layout == VERTEX_LAYOUT_PT)
	{
		m_id[VERTEX_ATTRIB_POSITION]	= attrib[0];
		m_id[VERTEX_ATTRIB_TEXCOORD]	= attrib[1];
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

	GenerateVAO();
}


void DefaultVertexBuffer::SetPosition(GLuint primitiveType, const vector<vec3>& position)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_id[VERTEX_ATTRIB_POSITION]);
	glBufferData(GL_ARRAY_BUFFER, position.size() * sizeof(vec3), position.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	m_vertexNum = (GLuint)position.size();
	m_PrimitiveType = primitiveType;
	Logger::GLError();
}

void DefaultVertexBuffer::SetNormal(const vector<vec3>& normal)
{
	if (HasNormal() == false)
	{
		assert(0);
		return;
	}

	glBindBuffer(GL_ARRAY_BUFFER, m_id[VERTEX_ATTRIB_NORMAL]);
	glBufferData(GL_ARRAY_BUFFER, normal.size() * sizeof(vec3), normal.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	Logger::GLError();
}

void DefaultVertexBuffer::SetColor(const vector<vec3>& color)
{
	if (HasColor() == false)
	{
		assert(0);
		return;
	}

	glBindBuffer(GL_ARRAY_BUFFER, m_id[VERTEX_ATTRIB_COLOR]);
	glBufferData(GL_ARRAY_BUFFER, color.size() * sizeof(vec3), color.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	Logger::GLError();
}

void DefaultVertexBuffer::SetTexcoord(const vector<vec2>& texcoord)
{
	if (HasTexCoord() == false)
	{
		assert(0);
		return;
	}

	glBindBuffer(GL_ARRAY_BUFFER, m_id[VERTEX_ATTRIB_TEXCOORD]);
	glBufferData(GL_ARRAY_BUFFER, texcoord.size() * sizeof(vec2), texcoord.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	Logger::GLError();
}

void DefaultVertexBuffer::SetIndex(const vector<int>& index)
{
	if (m_indexId == 0)
	{
		glGenBuffers(1, &m_indexId);
	}

	glBindVertexArray(m_vaoId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index.size() * sizeof(int), index.data(), GL_STATIC_DRAW);
	glBindVertexArray(0);
	m_indexSize = (GLuint)index.size();
	Logger::GLError();

}

void DefaultVertexBuffer::GenerateVAO()
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
		glEnableVertexAttribArray(VERTEX_ATTRIB_COLOR);
		glBindBuffer(GL_ARRAY_BUFFER, m_id[VERTEX_ATTRIB_COLOR]);
		glVertexAttribPointer(VERTEX_ATTRIB_COLOR, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	}

	if (HasTexCoord())
	{
		glEnableVertexAttribArray(VERTEX_ATTRIB_TEXCOORD);
		glBindBuffer(GL_ARRAY_BUFFER, m_id[VERTEX_ATTRIB_TEXCOORD]);
		glVertexAttribPointer(VERTEX_ATTRIB_TEXCOORD, 2, GL_FLOAT, GL_FALSE, 0,NULL);
	}

	glBindVertexArray(0);
	Logger::GLError();
}

void DefaultVertexBuffer::Dispose()
{
	for (int i = 0; i < VERTEX_ATTRIB_NUM; i++)
	{
		if (m_id[i] != 0)
		{
			glDeleteBuffers(1, &m_id[i]);
		}
	}

	if (m_vaoId != 0)
	{
		glDeleteVertexArrays(1, &m_vaoId);
	}

	if (m_indexId != 0)
	{
		glDeleteBuffers(1, &m_indexId);
	}
}

void DefaultVertexBuffer::Draw()
{
	glBindVertexArray(m_vaoId);
	if (HasIndex())
	{
		glDrawElements(m_PrimitiveType, m_indexSize, GL_UNSIGNED_INT, 0);
	}
	else
	{
		glDrawArrays(m_PrimitiveType, 0, m_vertexNum);
	}
	glBindVertexArray(0);
	Logger::GLError();
}

bool DefaultVertexBuffer::HasNormal()
{
	if (m_layout == VERTEX_LAYOUT_PN ||
		m_layout == VERTEX_LAYOUT_PNC ||
		m_layout == VERTEX_LAYOUT_PNCT)
	{
		return true;
	}

	return false;
}

bool DefaultVertexBuffer::HasColor()
{
	if (m_layout == VERTEX_LAYOUT_PC ||
		m_layout == VERTEX_LAYOUT_PNC ||
		m_layout == VERTEX_LAYOUT_PNCT)
	{
		return true;
	}

	return false;
}

bool DefaultVertexBuffer::HasTexCoord()
{
	if (m_layout == VERTEX_LAYOUT_PT ||
		m_layout == VERTEX_LAYOUT_PNCT)
	{
		return true;
	}

	return false;
}

bool DefaultVertexBuffer::HasIndex()
{
	if (m_indexId != 0)
	{
		return true;
	}

	return false;
}

int DefaultVertexBuffer::NumVertexAttrib()
{
	if (m_layout == VERTEX_LAYOUT_P)
	{
		return 1;
	}

	if (m_layout == VERTEX_LAYOUT_PC || 
		m_layout == VERTEX_LAYOUT_PN ||
		m_layout == VERTEX_LAYOUT_PT)
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

	assert(0);
	return 1;
}
}
}