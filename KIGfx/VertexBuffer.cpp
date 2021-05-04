namespace KI
{
namespace Gfx
{
VertexBuffer::VertexBuffer(const string& name)
{
	m_vaoId = 0;
	m_VertexSize = 0;
	m_instanceNum = 1;
	m_name = name;
}

void VertexBuffer::SetArrayBuffer(GLuint layout, shared_ptr<ArrayBuffer> pArrayBuffer)
{
	if (pArrayBuffer->IsGenerated() == false)
	{
		// need set value;
		assert(0);
		return;
	}

	Add(layout, pArrayBuffer);
	BindToVAO(layout);
}

shared_ptr<ArrayBuffer> VertexBuffer::GetArrayBuffer(GLuint location)
{
	return m_VertexInfo[location];
}

void VertexBuffer::Add(GLuint location, shared_ptr<ArrayBuffer> arrayBuffer)
{
	if (location > 16)
	{
		assert(0);
	}

	m_VertexInfo[location] = arrayBuffer;
}

void VertexBuffer::Remove(GLuint location)
{
	m_VertexInfo.erase(location);
}


void VertexBuffer::DrawByIndexBuffer(GLuint primitiveType, IndexBuffer* pIndexbuffer, GLuint first, GLuint count)
{
	if (m_vaoId == 0)
	{
		assert(0);
	}

	
	if (IsInstanceDraw())
	{
		glBindVertexArray(m_vaoId);
		BindAttribDivisor();
		pIndexbuffer->InstanceDraw(primitiveType, m_instanceNum);
		UnBindAttribDivisor();
		glBindVertexArray(0);
	}
	else
	{
		glBindVertexArray(m_vaoId);
		pIndexbuffer->Draw(primitiveType, first, count);
		glBindVertexArray(0);
	}

}

void VertexBuffer::Draw(GLuint primitiveType)
{
	if (m_VertexInfo[0] == nullptr ||
		m_VertexInfo[0]->Size() == 0)
	{
		assert(0);
	}

	Draw(primitiveType, 0, GetVertexSize());
}
void VertexBuffer::Draw(GLuint primitiveType, GLuint first, GLuint count)
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

void VertexBuffer::Dispose()
{
}

void VertexBuffer::BindToVAO(GLuint location)
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