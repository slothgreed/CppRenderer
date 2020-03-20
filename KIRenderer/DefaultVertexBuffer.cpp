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
		m_VertexInfo[VERTEX_ATTRIB_POSITION]->Set(position);
		BindToVAO(VERTEX_ATTRIB_POSITION);
	}
	else
	{
		m_VertexInfo[VERTEX_ATTRIB_POSITION]->Set(position);
	}

	SetPrimitiveType(primitiveType);
	Logger::GLError();
}

void DefaultVertexBuffer::SetNormal(const vector<vec3>& normal)
{
	if (m_VertexInfo[VERTEX_ATTRIB_NORMAL] == nullptr)
	{
		Add(VERTEX_ATTRIB_NORMAL, make_shared<ArrayBuffer>(GL_FLOAT, 3));
		m_VertexInfo[VERTEX_ATTRIB_NORMAL]->Set(normal);
		BindToVAO(VERTEX_ATTRIB_NORMAL);
	}
	else
	{
		m_VertexInfo[VERTEX_ATTRIB_NORMAL]->Set(normal);
	}

	Logger::GLError();
}

void DefaultVertexBuffer::SetColor(const vector<vec3>& color)
{
	if (m_VertexInfo[VERTEX_ATTRIB_COLOR] == nullptr)
	{
		Add(VERTEX_ATTRIB_COLOR, make_shared<ArrayBuffer>(GL_FLOAT, 3));
		m_VertexInfo[VERTEX_ATTRIB_COLOR]->Set(color);
		BindToVAO(VERTEX_ATTRIB_COLOR);
	}
	else
	{
		m_VertexInfo[VERTEX_ATTRIB_COLOR]->Set(color);
	}

	Logger::GLError();
}

void DefaultVertexBuffer::SetTexcoord(const vector<vec2>& texcoord)
{
	if (m_VertexInfo[VERTEX_ATTRIB_TEXCOORD] == nullptr)
	{
		Add(VERTEX_ATTRIB_TEXCOORD, make_shared<ArrayBuffer>(GL_FLOAT, 2));
		m_VertexInfo[VERTEX_ATTRIB_TEXCOORD]->Set(texcoord);
		BindToVAO(VERTEX_ATTRIB_TEXCOORD);
	}
	else
	{
		m_VertexInfo[VERTEX_ATTRIB_TEXCOORD]->Set(texcoord);
	}

	Logger::GLError();
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