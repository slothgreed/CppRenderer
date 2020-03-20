namespace KI
{
namespace Renderer
{
DefaultVertexBuffer::DefaultVertexBuffer()
{
}

DefaultVertexBuffer::~DefaultVertexBuffer()
{
	Dispose();
}

void DefaultVertexBuffer::SetPosition(GLuint primitiveType, const vector<vec3>& position)
{
	if (m_VertexInfo[VERTEX_ATTRIB_POSITION] == nullptr)
	{
		Add(VERTEX_ATTRIB_POSITION, make_shared<ArrayBuffer>(GL_FLOAT, 3));
		m_VertexInfo[VERTEX_ATTRIB_POSITION]->Generate();
		BindToVAO(VERTEX_ATTRIB_POSITION);
	}

	m_VertexInfo[VERTEX_ATTRIB_POSITION]->Set(position);
	SetVertexSize(m_VertexInfo[VERTEX_ATTRIB_POSITION]->Size());
	SetPrimitiveType(primitiveType);
}

void DefaultVertexBuffer::SetNormal(const vector<vec3>& normal)
{
	if (m_VertexInfo[VERTEX_ATTRIB_NORMAL] == nullptr)
	{
		Add(VERTEX_ATTRIB_NORMAL, make_shared<ArrayBuffer>(GL_FLOAT, 3));
		m_VertexInfo[VERTEX_ATTRIB_NORMAL]->Generate();
		BindToVAO(VERTEX_ATTRIB_NORMAL);
	}

	m_VertexInfo[VERTEX_ATTRIB_NORMAL]->Set(normal);
}

void DefaultVertexBuffer::SetColor(const vector<vec3>& color)
{
	if (m_VertexInfo[VERTEX_ATTRIB_COLOR] == nullptr)
	{
		Add(VERTEX_ATTRIB_COLOR, make_shared<ArrayBuffer>(GL_FLOAT, 3));
		m_VertexInfo[VERTEX_ATTRIB_COLOR]->Generate();
		BindToVAO(VERTEX_ATTRIB_COLOR);
	}

	m_VertexInfo[VERTEX_ATTRIB_COLOR]->Set(color);
}

void DefaultVertexBuffer::SetTexcoord(const vector<vec2>& texcoord)
{
	if (m_VertexInfo[VERTEX_ATTRIB_TEXCOORD] == nullptr)
	{
		Add(VERTEX_ATTRIB_TEXCOORD, make_shared<ArrayBuffer>(GL_FLOAT, 2));
		m_VertexInfo[VERTEX_ATTRIB_TEXCOORD]->Generate();
		BindToVAO(VERTEX_ATTRIB_TEXCOORD);
	}

	m_VertexInfo[VERTEX_ATTRIB_TEXCOORD]->Set(texcoord);
}


void DefaultVertexBuffer::SetTranslate(const vector<vec3>& texcoord)
{
	if (m_VertexInfo[VERTEX_ATTRIB_TRANSLATE] == nullptr)
	{
		Add(VERTEX_ATTRIB_TRANSLATE, make_shared<ArrayBuffer>(GL_FLOAT, 3));
		m_VertexInfo[VERTEX_ATTRIB_TRANSLATE]->Generate();
		BindToVAO(VERTEX_ATTRIB_TRANSLATE);
	}

	m_VertexInfo[VERTEX_ATTRIB_TRANSLATE]->Set(texcoord);
}

bool DefaultVertexBuffer::HasAttribute(VERTEX_ATTRIB attribute)
{
	if (m_VertexInfo[attribute] != NULL &&
		m_VertexInfo[attribute]->IsGenerated())
	{
		return true;
	}

	return false;
}

void DefaultVertexBuffer::BindAttribDivisor()
{
	glVertexAttribDivisor(VERTEX_ATTRIB_POSITION, 0);
	
	if (HasAttribute(VERTEX_ATTRIB_COLOR))
	{
		glVertexAttribDivisor(VERTEX_ATTRIB_COLOR, 1);
	}

	if (HasAttribute(VERTEX_ATTRIB_TEXCOORD))
	{
		glVertexAttribDivisor(VERTEX_ATTRIB_TEXCOORD, 1);
	}

	if (HasAttribute(VERTEX_ATTRIB_TRANSLATE))
	{
		glVertexAttribDivisor(VERTEX_ATTRIB_TRANSLATE, 1);
	}
}

void DefaultVertexBuffer::UnBindAttribDivisor()
{
	glVertexAttribDivisor(VERTEX_ATTRIB_POSITION, 0);

	if (HasAttribute(VERTEX_ATTRIB_COLOR))
	{
		glVertexAttribDivisor(VERTEX_ATTRIB_COLOR, 0);
	}

	if (HasAttribute(VERTEX_ATTRIB_TEXCOORD))
	{
		glVertexAttribDivisor(VERTEX_ATTRIB_TEXCOORD, 0);
	}

	if (HasAttribute(VERTEX_ATTRIB_TRANSLATE))
	{
		glVertexAttribDivisor(VERTEX_ATTRIB_TRANSLATE, 0);
	}
}

GLuint DefaultVertexBuffer::Layout()
{
	GLuint layout = 0;
	if (HasAttribute(VERTEX_ATTRIB_POSITION))
	{
		layout |= VERTEX_LAYOUT_POSITION;
	}
	
	if (HasAttribute(VERTEX_ATTRIB_NORMAL))
	{
		layout |= VERTEX_LAYOUT_NORMAL;
	}

	if (HasAttribute(VERTEX_ATTRIB_COLOR))
	{
		layout |= VERTEX_LAYOUT_COLOR;
	}

	if (HasAttribute(VERTEX_ATTRIB_TEXCOORD))
	{
		layout |= VERTEX_LAYOUT_TEXCOORD;
	}

	return layout;
}
}
}