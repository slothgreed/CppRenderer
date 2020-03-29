namespace KI
{
namespace Renderer
{

DefaultFragCode::DefaultFragCode()
	:IShaderCode(
		string(SHADER_DIRECTORY) + 
		string(SHADER_DEFAULT) + 
		string(SHADER_EXT_FRAG))
{
	m_useGBuffer = false;
	m_useNormal = false;
	m_useColor = false;
	m_useTexcoord = false;
	m_useTexture0 = false;
	m_useShading = false;
}

DefaultFragCode::~DefaultFragCode()
{
}

void DefaultFragCode::GetDefineCode(string& code)
{
	if (m_useGBuffer)
		code += USE_GBUFFER;
	if (m_useNormal)
		code += USE_NORMAL;
	if (m_useColor)
		code += USE_COLOR;
	if (m_useTexcoord)
		code += USE_TEXCOORD;
	if (m_useTexture0)
		code += USE_TEXTURE0;
	if (m_useShading)
		code += USE_SHADING;
}

bool DefaultFragCode::Compare(IShaderCode* pShaderCode)
{
	if (pShaderCode->Type() == SHADER_TYPE_DEFAULT)
	{
		DefaultFragCode* pDefine = (DefaultFragCode*)(pShaderCode);
		if (m_useGBuffer == pDefine->m_useGBuffer &&
			m_useNormal == pDefine->m_useNormal &&
			m_useColor == pDefine->m_useColor &&
			m_useTexcoord == pDefine->m_useTexcoord &&
			m_useTexture0 == pDefine->m_useTexture0 &&
			m_useShading == pDefine->m_useShading)
		{
			return true;
		}
	}

	return false;
}

void DefaultFragCode::SetShaderDefine(VERTEX_LAYOUT layout)
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
		m_useTexture0 = true;
	}
}
}
}