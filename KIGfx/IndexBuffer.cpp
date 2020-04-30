namespace KI
{
namespace Gfx
{
IndexBuffer::IndexBuffer()
{
	m_Id = 0;
}

IndexBuffer::~IndexBuffer()
{
	Dispose();
}

void IndexBuffer::Generate()
{
	if (m_Id == 0)
	{
		glGenBuffers(1, &m_Id);
	}
}

void IndexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
}

void IndexBuffer::UnBind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::Set(const vector<int>& index)
{
	if (IsGenerated() == false)
	{
		Generate();
	}

	Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index.size() * sizeof(int), index.data(), GL_STATIC_DRAW);
	// UnBind(); ‰½ŒÌ‚©•s—v
	m_indexSize = (GLuint)index.size();
	Logger::GLError();
}

void IndexBuffer::Dispose()
{
	if (m_Id != 0)
	{
		glDeleteBuffers(1, &m_Id);
	}

	m_Id = 0;
}

void IndexBuffer::Draw(GLuint primitiveType, GLuint first, GLuint count)
{
	Bind();
	if (first == 0 && count == 0)
	{
		glDrawElements(primitiveType, Size(), GL_UNSIGNED_INT, 0);
	}
	else
	{
		glDrawElements(primitiveType, count, GL_UNSIGNED_INT, (void*)first);
	}
	UnBind();
}

void IndexBuffer::InstanceDraw(GLuint primitiveType, int num)
{
	Bind();
	glDrawElementsInstanced(primitiveType, Size(), GL_UNSIGNED_INT, NULL, num);
	UnBind();
}

}
}