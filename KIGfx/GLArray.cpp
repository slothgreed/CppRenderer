#include "GLArray.h"
namespace KI
{
namespace Gfx
{
GLArray::GLArray()
{
	m_dataType = GL_FLOAT;
	m_data = NULL;
	m_dataSize = 0;
	m_arraySize = 0;
}

GLArray::~GLArray()
{
	if (m_data != NULL)
	{
		delete m_data;
		m_data = NULL;
	}
}

void GLArray::NewArray(GLenum dataType, int dataSize, int arraySize)
{
	if (dataType == GL_FLOAT)
	{
		m_data = new GLfloat[dataSize * arraySize];
		m_dataType = GL_FLOAT;
	}
	else if (dataType == GL_INT ||
		dataType == GL_UNSIGNED_INT)
	{
		m_data = new GLint[dataSize * arraySize];
		m_dataType = GL_INT;
	}
	else
	{
		assert(0);
	}

	m_dataSize = GL_INT;
	m_arraySize = arraySize;
}

int GLArray::GetInt(int index)
{
	if (m_dataType == GL_INT)
	{
		return ((GLint*)m_data)[index];
	}
	else
	{
		assert(0);
		return 0;
	}
}

float GLArray::GetFloat(int index)
{
	if (m_dataType == GL_FLOAT)
	{
		return ((GLfloat*)m_data)[index];
	}
	else
	{
		assert(0);
		return 0.0f;
	}
}

vec2 GLArray::GetVector2(int index)
{
	if (m_dataType == GL_FLOAT)
	{
		return vec2(
			((GLfloat*)m_data)[2 * index],
			((GLfloat*)m_data)[2 * index + 1]);
	}
	else if (m_dataType == GL_INT)
	{
		return vec2(
			((GLint*)m_data)[2 * index],
			((GLint*)m_data)[2 * index + 1]);
	}
	else 
	{
		assert(0);
		return vec2(0);
	}
}


vec3 GLArray::GetVector3(int index)
{
	if (m_dataType == GL_FLOAT)
	{
		return vec3(
			((GLfloat*)m_data)[3 * index],
			((GLfloat*)m_data)[3 * index + 1],
			((GLfloat*)m_data)[3 * index + 2]);
	}
	else if (m_dataType == GL_INT)
	{
		return vec3(
			((GLint*)m_data)[3 * index],
			((GLint*)m_data)[3 * index + 1],
			((GLint*)m_data)[3 * index + 2]);
	}
	else
	{
		assert(0);
		return vec3(0);
	}
}


vec4 GLArray::GetVector4(int index)
{
	if (m_dataType == GL_FLOAT)
	{
		return vec4(
			((GLfloat*)m_data)[4 * index],
			((GLfloat*)m_data)[4 * index + 1],
			((GLfloat*)m_data)[4 * index + 2],
			((GLfloat*)m_data)[4 * index + 3]);
	}
	else if (m_dataType == GL_INT)
	{
		return vec4(
			((GLint*)m_data)[4 * index],
			((GLint*)m_data)[4 * index + 1],
			((GLint*)m_data)[4 * index + 2],
			((GLint*)m_data)[4 * index + 3]);
	}
	else
	{
		assert(0);
		return vec4(0);
	}
}


void* GLArray::Data()
{
	return m_data;
}

int GLArray::GetSize()
{
	return m_arraySize;
}
}
}
