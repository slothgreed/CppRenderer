namespace KI
{
namespace Gfx
{
IVertexBuffer::IVertexBuffer()
{
	m_vaoId = 0;
	m_Size = 0;
	m_PrimitiveType = GL_NONE;
	m_isInstanceDraw = false;
}
void IVertexBuffer::Add(GLuint location, shared_ptr<ArrayBuffer> arrayBuffer)
{
	if (location > 16)
	{
		assert(0);
	}

	m_VertexInfo[location] = arrayBuffer;
}

void IVertexBuffer::Remove(GLuint location)
{
	m_VertexInfo.erase(location);
}

void IVertexBuffer::SetPrimitiveType(GLuint primitiveType)
{
	m_PrimitiveType = primitiveType;
}

void IVertexBuffer::Draw(IndexBuffer* pIndexbuffer)
{
	if (m_vaoId == 0)
	{
		assert(0);
	}

	glBindVertexArray(m_vaoId);
	
	if (IsInstanceDraw())
	{
		BindAttribDivisor();
	}
	
	pIndexbuffer->Draw();
	glBindVertexArray(0);

	if (IsInstanceDraw())
	{
		UnBindAttribDivisor();
	}

}

void IVertexBuffer::Draw()
{
	if (m_VertexInfo[0] == nullptr ||
		m_VertexInfo[0]->Size() == 0)
	{
		assert(0);
	}

	GLuint size = m_VertexInfo[0]->Size();
	Draw(m_PrimitiveType, 0, size);
}
void IVertexBuffer::Draw(GLuint primitiveType, GLuint first, GLuint count)
{
	if (m_vaoId == 0)
	{
		assert(0);
	}

	if (count == 0)
	{
		assert(0);
	}

	if (IsInstanceDraw())
	{
		BindAttribDivisor();
	}

	glBindVertexArray(m_vaoId);
	glDrawArrays(primitiveType, first, count);
	glBindVertexArray(0);

	if (IsInstanceDraw())
	{
		UnBindAttribDivisor();
	}

	Logger::GLError();
}

void IVertexBuffer::Dispose()
{
	map<int, shared_ptr<ArrayBuffer>> itr;

	for (auto itr = m_VertexInfo.begin(); itr != m_VertexInfo.end(); itr++)
	{
		if (itr->second != nullptr)
		{
			itr->second->Dispose();
		}
	}
}

void IVertexBuffer::BindToVAO(GLuint location)
{
	if (m_vaoId == 0)
	{
		glGenVertexArrays(1, &m_vaoId);
	}

	glBindVertexArray(m_vaoId);
	auto pArrayBuffer = m_VertexInfo[location];
	if (pArrayBuffer == nullptr)
	{
		assert(0);
	}

	glEnableVertexAttribArray(location);
	glBindBuffer(GL_ARRAY_BUFFER, pArrayBuffer->ID());
	glVertexAttribPointer(
		location,
		pArrayBuffer->ComponentSize(),
		pArrayBuffer->ComponentType(),
		GL_FALSE,
		0,
		NULL);

	glBindVertexArray(0);
	Logger::GLError();
}
}
}