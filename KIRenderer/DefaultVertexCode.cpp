namespace KI
{
namespace Renderer
{

DefaultVertexCode::DefaultVertexCode()
	:IShaderCode(
		string(SHADER_DIRECTORY) +
		string(SHADER_DEFAULT) +
		string(SHADER_EXT_VERTEX))
{
	m_useGBuffer = false;
	m_useNormal = false;
	m_useColor = false;
	m_useTexcoord = false;
	m_useInstance = false;
	m_useShading = false;
}

DefaultVertexCode::~DefaultVertexCode()
{
}

void DefaultVertexCode::GetDefineCode(string& code)
{
	if (m_useNormal)
		code += USE_NORMAL;
	if (m_useColor)
		code += USE_COLOR;
	if (m_useTexcoord)
		code += USE_TEXCOORD;
	if (m_useGBuffer)
		code += USE_GBUFFER;
	if (m_useInstance)
		code += USE_INSTANCE;
}

bool DefaultVertexCode::Compare(IShaderCode* pShaderCode)
{
	if (pShaderCode->Type() == SHADER_TYPE_DEFAULT)
	{
		DefaultVertexCode* pDefine = (DefaultVertexCode*)(pShaderCode);
		if (m_useGBuffer == pDefine->m_useGBuffer &&
			m_useNormal == pDefine->m_useNormal &&
			m_useColor == pDefine->m_useColor &&
			m_useTexcoord == pDefine->m_useTexcoord &&
			m_useInstance == pDefine->m_useInstance)
		{
			return true;
		}
	}

	return false;
}
void DefaultVertexCode::SetShaderDefine(VERTEX_LAYOUT layout)
{
	if (layout & VERTEX_LAYOUT_NORMAL)
	{
		m_useNormal = true;
	}

	if (layout & VERTEX_LAYOUT_COLOR)
	{
		m_useColor = true;
	}

	if (layout & VERTEX_LAYOUT_TEXCOORD)
	{
		m_useTexcoord = true;
	}

	if (layout & VERTEX_LAYOUT_INSTANCE_MATRIX0 ||
		layout & VERTEX_LAYOUT_INSTANCE_MATRIX1 ||
		layout & VERTEX_LAYOUT_INSTANCE_MATRIX2 ||
		layout & VERTEX_LAYOUT_INSTANCE_MATRIX3)
	{
		m_useInstance = true;
	}
}
}
}


