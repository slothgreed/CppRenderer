namespace KI
{
namespace Gfx
{
IVertexBuffer::IVertexBuffer()
{
	m_vaoId = 0;
	m_VertexSize = 0;
	m_PrimitiveType = GL_NONE;
	m_instanceNum = 1;
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

	
	if (IsInstanceDraw())
	{
		glBindVertexArray(m_vaoId);
		BindAttribDivisor();
		pIndexbuffer->InstanceDraw(m_instanceNum);
		UnBindAttribDivisor();
		glBindVertexArray(0);
	}
	else
	{
		glBindVertexArray(m_vaoId);
		pIndexbuffer->Draw();
		glBindVertexArray(0);
	}

}

void IVertexBuffer::Draw()
{
	if (m_VertexInfo[0] == nullptr ||
		m_VertexInfo[0]->Size() == 0)
	{
		assert(0);
	}

	Draw(m_PrimitiveType, 0, GetVertexSize());
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
		glBindVertexArray(m_vaoId);
		glDrawArraysInstanced(primitiveType, first, count, m_instanceNum);
		glBindVertexArray(0);
		UnBindAttribDivisor();
	}
	else
	{
		glBindVertexArray(m_vaoId);
		glDrawArrays(primitiveType, first, count);
		glBindVertexArray(0);
	}

	Logger::GLError();
}

void IVertexBuffer::Dispose()
{
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