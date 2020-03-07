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

bool IndexBuffer::IsGenerated()
{
	return m_Id != 0;
}

void IndexBuffer::Set(GLuint primitiveType, const vector<int>& index)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index.size() * sizeof(int), index.data(), GL_STATIC_DRAW);
	m_PrimitiveType = primitiveType;
	m_indexSize = index.size();
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

void IndexBuffer::Draw()
{
	glDrawElements(m_PrimitiveType, Size(), GL_UNSIGNED_INT, 0);
}
}
}