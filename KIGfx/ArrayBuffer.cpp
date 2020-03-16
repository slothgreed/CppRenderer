namespace KI
{
namespace Gfx
{
ArrayBuffer::ArrayBuffer()
{
	m_Id = 0;
	m_Size = 0;
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
		assert(0);
		return;
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

void ArrayBuffer::Set(const vector<vec3>& data)
{
	if (m_Id == 0)
	{
		assert(0);
		return;
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
	if (m_Id == 0)
	{
		assert(0);
		return;
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
		glBufferData(GL_ARRAY_BUFFER, m_Size, data.data(), GL_STATIC_DRAW);
	}
	else
	{
		m_Size = size;
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