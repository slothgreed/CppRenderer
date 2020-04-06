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
	m_planePosition = false;
	m_useTexcoord = false;
	m_useInstance = false;
	m_outInstance = false;
	m_useShading = false;
	m_viewNormal = false;
}

DefaultVertexCode::~DefaultVertexCode()
{
}

void DefaultVertexCode::GetDefineCode(string& code)
{
	if (m_planePosition){
		code += OUT_PLANE_POSITION;
	}

	if (m_useNormal) {
		code += IN_NORMAL;
		code += OUT_NORMAL;
	}
	if (m_useColor) {
		code += IN_COLOR;
	}

	code += OUT_COLOR;	// 色の出力は必ずする．

	if (m_useTexcoord) {
		code += IN_TEXCOORD;
		code += OUT_TEXCOORD;
	}
	if (m_useGBuffer) {
		code += USE_GBUFFER;
	}
	if (m_useInstance) {
		code += IN_INSTANCE;
		if (m_outInstance) {
			code += OUT_INSTANCE;
		}
	}
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
			m_useInstance == pDefine->m_useInstance &&
			m_outInstance == pDefine->m_outInstance &&
			m_planePosition == pDefine->m_planePosition)
		{
			return true;
		}
	}

	return false;
}

void DefaultVertexCode::SetShaderDefine(SHADER_TYPE type)
{
	if (type == SHADER_TYPE::SHADER_TYPE_NORMALVISUALIZE)
	{
		m_useNormal = true;
		m_planePosition = true;
	}
	else
	{
		assert(0);
	}
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


