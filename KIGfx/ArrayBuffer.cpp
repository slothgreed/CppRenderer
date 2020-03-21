namespace KI
{
namespace Gfx
{
ArrayBuffer::ArrayBuffer(GLuint componentType, GLuint componentSize)
{
	m_Id = 0;
	m_Size = 0;
	m_ComponentType = componentType;
	m_ComponentSize = componentSize;
}

ArrayBuffer::~ArrayBuffer()
{
	Dispose();
}

void ArrayBuffer::Generate()
{
	if (m_Id == 0)
	{
		glGenBuffers(1, &m_Id);
	}
}

void ArrayBuffer::Set(const vector<vec2>& data)
{
	if (m_Id == 0)
	{
		Generate();
	}

	if (m_ComponentType != GL_FLOAT || 
		m_ComponentSize != 2)
	{
		assert(0);
	}

	int size = (int)data.size() * sizeof(vec2);
	if (size == 0)
	{
		assert(0);
		return;
	}

	glBindBuffer(GL_ARRAY_BUFFER, m_Id);
	if (m_Size != size)
	{
		m_Size = size;
		glBufferData(GL_ARRAY_BUFFER, m_Size, data.data(), GL_STATIC_DRAW);
	}
	else
	{
		glBufferSubData(GL_ARRAY_BUFFER, 0, m_Size, data.data());
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	Logger::GLError();
}

void ArrayBuffer::Set(const vector<vec4>& data)
{
	if (m_Id == 0)
	{
		Generate();
	}

	if (m_ComponentType != GL_FLOAT ||
		m_ComponentSize != 4)
	{
		assert(0);
	}

	int size = (int)data.size() * sizeof(vec4);
	if (size == 0)
	{
		assert(0);
		return;
	}

	glBindBuffer(GL_ARRAY_BUFFER, m_Id);
	if (m_Size != size)
	{
		m_Size = size;
		glBufferData(GL_ARRAY_BUFFER, m_Size, data.data(), GL_STATIC_DRAW);
	}
	else
	{
		glBufferSubData(GL_ARRAY_BUFFER, 0, m_Size, data.data());
	}

	Logger::GLError();
}

void ArrayBuffer::Set(const vector<vec3>& data)
{
	if (m_Id == 0)
	{
		Generate();
	}

	if (m_ComponentType != GL_FLOAT ||
		m_ComponentSize != 3)
	{
		assert(0);
	}

	int size = (int)data.size() * sizeof(vec3);
	if (size == 0)
	{
		assert(0);
		return;
	}
	
	glBindBuffer(GL_ARRAY_BUFFER, m_Id);
	if (m_Size != size)
	{
		m_Size = size;
		glBufferData(GL_ARRAY_BUFFER, m_Size, data.data(), GL_STATIC_DRAW);
	}
	else
	{
		glBufferSubData(GL_ARRAY_BUFFER, 0, m_Size, data.data());
	}

	Logger::GLError();
}

void ArrayBuffer::Set(const vector<int>& data)
{
	if (m_ComponentType != GL_INT ||
		m_ComponentSize != 1)
	{
		assert(0);
	}

	if (m_Id == 0)
	{
		Generate();
	}

	int size = (int)data.size() * sizeof(int);
	if (size == 0)
	{
		assert(0);
		return;
	}

	glBindBuffer(GL_ARRAY_BUFFER, m_Id);
	if (m_Size != size)
	{
		m_Size = size;
		m_ComponentType = GL_INT;
		m_ComponentSize = 1; //TODO:check;
		assert(0);
		glBufferData(GL_ARRAY_BUFFER, m_Size, data.data(), GL_STATIC_DRAW);
	}
	else
	{
		glBufferSubData(GL_ARRAY_BUFFER, 0, m_Size, data.data());
	}
	Logger::GLError();
}

void ArrayBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_Id);
}

void ArrayBuffer::UnBind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ArrayBuffer::Dispose()
{
	if (m_Id != 0)
	{
		glDeleteBuffers(1, &m_Id);
	}

	m_Id = 0;
	m_Size = 0;
}


}
}