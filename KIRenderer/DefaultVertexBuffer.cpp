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

void DefaultVertexBuffer::SetArrayBuffer(GLuint layout, shared_ptr<ArrayBuffer> pArrayBuffer)
{
	if (pArrayBuffer->IsGenerated() == false)
	{
		// need set value;
		assert(0);
		return;
	}

	bool varidator = false;
	for (int i = 0; i < VERTEX_ATTRIB_NUM; i++)
	{
		if (layout == i)
		{
			varidator = true;
			break;
		}
	}

	if (varidator == false) {
		assert(0);
	}

	if (m_VertexInfo[layout] == nullptr)
	{
		Add(layout, pArrayBuffer);
		BindToVAO(layout);
	}
}

shared_ptr<ArrayBuffer> DefaultVertexBuffer::GetArrayBuffer(GLuint location)
{
	bool varidator = false;
	for (int i = 0; i < VERTEX_ATTRIB_NUM; i++)
	{
		if (location == i)
		{
			varidator = true;
			break;
		}
	}

	if (varidator == false) {
		assert(0);
	}

	return m_VertexInfo[location];

}
void DefaultVertexBuffer::SetPosition(const vector<vec3>& position)
{
	if (m_VertexInfo[VERTEX_ATTRIB_POSITION] == nullptr)
	{
		Add(VERTEX_ATTRIB_POSITION, make_shared<ArrayBuffer>(GL_FLOAT, 3));
		m_VertexInfo[VERTEX_ATTRIB_POSITION]->Generate();
		BindToVAO(VERTEX_ATTRIB_POSITION);
	}

	m_VertexInfo[VERTEX_ATTRIB_POSITION]->Set(position);
	SetVertexSize((int)position.size());
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


void DefaultVertexBuffer::SetInstanceMatrix(const vector<mat4>& matrix)
{
	if (m_VertexInfo[VERTEX_ATTRIB_INSTANCE_MATRIX0] == nullptr ||
		m_VertexInfo[VERTEX_ATTRIB_INSTANCE_MATRIX1] == nullptr ||
		m_VertexInfo[VERTEX_ATTRIB_INSTANCE_MATRIX2] == nullptr ||
		m_VertexInfo[VERTEX_ATTRIB_INSTANCE_MATRIX3] == nullptr)
	{
		Add(VERTEX_ATTRIB_INSTANCE_MATRIX0, make_shared<ArrayBuffer>(GL_FLOAT, 4));
		Add(VERTEX_ATTRIB_INSTANCE_MATRIX1, make_shared<ArrayBuffer>(GL_FLOAT, 4));
		Add(VERTEX_ATTRIB_INSTANCE_MATRIX2, make_shared<ArrayBuffer>(GL_FLOAT, 4));
		Add(VERTEX_ATTRIB_INSTANCE_MATRIX3, make_shared<ArrayBuffer>(GL_FLOAT, 4));
		m_VertexInfo[VERTEX_ATTRIB_INSTANCE_MATRIX0]->Generate();
		m_VertexInfo[VERTEX_ATTRIB_INSTANCE_MATRIX1]->Generate();
		m_VertexInfo[VERTEX_ATTRIB_INSTANCE_MATRIX2]->Generate();
		m_VertexInfo[VERTEX_ATTRIB_INSTANCE_MATRIX3]->Generate();
		BindToVAO(VERTEX_ATTRIB_INSTANCE_MATRIX0);
		BindToVAO(VERTEX_ATTRIB_INSTANCE_MATRIX1);
		BindToVAO(VERTEX_ATTRIB_INSTANCE_MATRIX2);
		BindToVAO(VERTEX_ATTRIB_INSTANCE_MATRIX3);
	}

	vector<vec4> row0;
	vector<vec4> row1;
	vector<vec4> row2;
	vector<vec4> row3;
	for (int i = 0; i < matrix.size(); i++)
	{
		row0.push_back(vec4(matrix[i][0][0], matrix[i][0][1], matrix[i][0][2], matrix[i][0][3]));
		row1.push_back(vec4(matrix[i][1][0], matrix[i][1][1], matrix[i][1][2], matrix[i][1][3]));
		row2.push_back(vec4(matrix[i][2][0], matrix[i][2][1], matrix[i][2][2], matrix[i][2][3]));
		row3.push_back(vec4(matrix[i][3][0], matrix[i][3][1], matrix[i][3][2], matrix[i][3][3]));
	
		//row0.push_back(vec4(matrix[i][0][0], matrix[i][1][0], matrix[i][2][0], matrix[i][3][0]));
		//row1.push_back(vec4(matrix[i][0][1], matrix[i][1][1], matrix[i][2][1], matrix[i][3][1]));
		//row2.push_back(vec4(matrix[i][0][2], matrix[i][1][2], matrix[i][2][2], matrix[i][3][2]));
		//row3.push_back(vec4(matrix[i][0][3], matrix[i][1][3], matrix[i][2][3], matrix[i][3][3]));
	}

	m_VertexInfo[VERTEX_ATTRIB_INSTANCE_MATRIX0]->Set(row0);
	m_VertexInfo[VERTEX_ATTRIB_INSTANCE_MATRIX1]->Set(row1);
	m_VertexInfo[VERTEX_ATTRIB_INSTANCE_MATRIX2]->Set(row2);
	m_VertexInfo[VERTEX_ATTRIB_INSTANCE_MATRIX3]->Set(row3);
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

	if (HasAttribute(VERTEX_ATTRIB_INSTANCE_MATRIX0) ||
		HasAttribute(VERTEX_ATTRIB_INSTANCE_MATRIX1) ||
		HasAttribute(VERTEX_ATTRIB_INSTANCE_MATRIX2) ||
		HasAttribute(VERTEX_ATTRIB_INSTANCE_MATRIX3))
	{
		glVertexAttribDivisor(VERTEX_ATTRIB_INSTANCE_MATRIX0, 1);
		glVertexAttribDivisor(VERTEX_ATTRIB_INSTANCE_MATRIX1, 1);
		glVertexAttribDivisor(VERTEX_ATTRIB_INSTANCE_MATRIX2, 1);
		glVertexAttribDivisor(VERTEX_ATTRIB_INSTANCE_MATRIX3, 1);
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

	if (HasAttribute(VERTEX_ATTRIB_INSTANCE_MATRIX0) ||
		HasAttribute(VERTEX_ATTRIB_INSTANCE_MATRIX1) ||
		HasAttribute(VERTEX_ATTRIB_INSTANCE_MATRIX2) ||
		HasAttribute(VERTEX_ATTRIB_INSTANCE_MATRIX3))
	{
		glVertexAttribDivisor(VERTEX_ATTRIB_INSTANCE_MATRIX0, 0);
		glVertexAttribDivisor(VERTEX_ATTRIB_INSTANCE_MATRIX1, 0);
		glVertexAttribDivisor(VERTEX_ATTRIB_INSTANCE_MATRIX2, 0);
		glVertexAttribDivisor(VERTEX_ATTRIB_INSTANCE_MATRIX3, 0);
	}
}

VERTEX_LAYOUT DefaultVertexBuffer::Layout()
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

	if (HasAttribute(VERTEX_ATTRIB_INSTANCE_MATRIX0) ||
		HasAttribute(VERTEX_ATTRIB_INSTANCE_MATRIX1) ||
		HasAttribute(VERTEX_ATTRIB_INSTANCE_MATRIX2) ||
		HasAttribute(VERTEX_ATTRIB_INSTANCE_MATRIX3))
	{
		layout |= VERTEX_LAYOUT_INSTANCE_MATRIX0;
		layout |= VERTEX_LAYOUT_INSTANCE_MATRIX1;
		layout |= VERTEX_LAYOUT_INSTANCE_MATRIX2;
		layout |= VERTEX_LAYOUT_INSTANCE_MATRIX3;
	}

	

	return (VERTEX_LAYOUT)layout;
}
}
}