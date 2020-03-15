namespace KI
{
namespace Renderer
{
DefaultVertexBuffer::DefaultVertexBuffer()
{
	m_vaoId = 0;
}

DefaultVertexBuffer::~DefaultVertexBuffer()
{
	Dispose();
}

void DefaultVertexBuffer::Generate(VERTEX_LAYOUT layout)
{
	m_layout = layout;

	if (m_layout == VERTEX_LAYOUT_P)
	{
		m_id[VERTEX_ATTRIB_POSITION].Generate();
	}
	else if(m_layout == VERTEX_LAYOUT_PN)
	{
		m_id[VERTEX_ATTRIB_POSITION].Generate();
		m_id[VERTEX_ATTRIB_NORMAL].Generate();
	}
	else if (m_layout == VERTEX_LAYOUT_PC)
	{
		m_id[VERTEX_ATTRIB_POSITION].Generate();
		m_id[VERTEX_ATTRIB_COLOR].Generate();
	}
	else if (m_layout == VERTEX_LAYOUT_PT)
	{
		m_id[VERTEX_ATTRIB_POSITION].Generate();
		m_id[VERTEX_ATTRIB_TEXCOORD].Generate();
	}
	else if (m_layout == VERTEX_LAYOUT_PNC)
	{
		m_id[VERTEX_ATTRIB_POSITION].Generate();
		m_id[VERTEX_ATTRIB_NORMAL].Generate();
		m_id[VERTEX_ATTRIB_COLOR].Generate();
	}
	else if(m_layout == VERTEX_LAYOUT_PNCT)
	{
		m_id[VERTEX_ATTRIB_POSITION].Generate();
		m_id[VERTEX_ATTRIB_NORMAL].Generate();
		m_id[VERTEX_ATTRIB_COLOR].Generate();
		m_id[VERTEX_ATTRIB_TEXCOORD].Generate();
	}
	else
	{
		assert(0);
	}

	Logger::GLError();

	GenerateVAO();
}


void DefaultVertexBuffer::SetPosition(GLuint primitiveType, const vector<vec3>& position)
{
	m_id[VERTEX_ATTRIB_POSITION].Set(position);
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

	m_id[VERTEX_ATTRIB_NORMAL].Set(normal);
	Logger::GLError();
}

void DefaultVertexBuffer::SetColor(const vector<vec3>& color)
{
	if (HasColor() == false)
	{
		assert(0);
		return;
	}

	m_id[VERTEX_ATTRIB_COLOR].Set(color);
	Logger::GLError();
}

void DefaultVertexBuffer::SetTexcoord(const vector<vec2>& texcoord)
{
	if (HasTexCoord() == false)
	{
		assert(0);
		return;
	}

	m_id[VERTEX_ATTRIB_TEXCOORD].Set(texcoord);
	Logger::GLError();
}

void DefaultVertexBuffer::SetIndex(GLuint primitiveType, const vector<int>& index)
{
	if (m_indexBuffer.IsGenerated() == false)
	{
		m_indexBuffer.Generate();
	}

	glBindVertexArray(m_vaoId);
	m_indexBuffer.Set(primitiveType, index);
	glBindVertexArray(0);
	Logger::GLError();

}

void DefaultVertexBuffer::GenerateVAO()
{
	glGenVertexArrays(1, &m_vaoId);
	glBindVertexArray(m_vaoId);
	glEnableVertexAttribArray(VERTEX_ATTRIB_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, m_id[VERTEX_ATTRIB_POSITION].ID());
	glVertexAttribPointer(VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	if (HasNormal())
	{
		glEnableVertexAttribArray(VERTEX_ATTRIB_NORMAL);
		glBindBuffer(GL_ARRAY_BUFFER, m_id[VERTEX_ATTRIB_NORMAL].ID());
		glVertexAttribPointer(VERTEX_ATTRIB_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	}

	if (HasColor())
	{
		glEnableVertexAttribArray(VERTEX_ATTRIB_COLOR);
		glBindBuffer(GL_ARRAY_BUFFER, m_id[VERTEX_ATTRIB_COLOR].ID());
		glVertexAttribPointer(VERTEX_ATTRIB_COLOR, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	}

	if (HasTexCoord())
	{
		glEnableVertexAttribArray(VERTEX_ATTRIB_TEXCOORD);
		glBindBuffer(GL_ARRAY_BUFFER, m_id[VERTEX_ATTRIB_TEXCOORD].ID());
		glVertexAttribPointer(VERTEX_ATTRIB_TEXCOORD, 2, GL_FLOAT, GL_FALSE, 0,NULL);
	}

	glBindVertexArray(0);
	Logger::GLError();
}

void DefaultVertexBuffer::Dispose()
{
	for (int i = 0; i < VERTEX_ATTRIB_NUM; i++)
	{
		m_id[i].Dispose();
	}

	if (m_vaoId != 0)
	{
		glDeleteVertexArrays(1, &m_vaoId);
	}

	m_indexBuffer.Dispose();
}

void DefaultVertexBuffer::Draw()
{
	glBindVertexArray(m_vaoId);
	if (HasIndex())
	{
		m_indexBuffer.Draw();
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
	if (m_indexBuffer.IsGenerated())
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