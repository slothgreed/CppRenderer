
namespace KI
{
namespace ShaderLib
{

VertexShading::VertexShading(VERTEX_SHADING_TYPE type)
{
	m_Type = type;
}

VertexShading::~VertexShading()
{
}

bool VertexShading::Compare(IShading* pShading)
{
	auto pVertexShading = dynamic_cast<VertexShading*>(pShading);
	if (pVertexShading == nullptr)
	{
		return false;
	}

	if (m_Type == pVertexShading->Type())
	{
		return true;
	}

	return false;
}

bool VertexShading::NewShaderCompare(IShaderChunk* pTarget)
{
	auto pVertexShading = dynamic_cast<VertexShading*>(pTarget);
	
	return Compare(pVertexShading);
}

shared_ptr<IShaderCode> VertexShading::NewShaderCode(IShaderBuildInfo* pBuildInfo, SHADER_PROGRAM_TYPE type)
{
	if (type == SHADER_PROGRAM_VERTEX) {
		return make_shared<VertexShadingVertexCode>(m_Type);
	}
	else if (type == SHADER_PROGRAM_FRAG)
	{
		return make_shared<VertexShadingFragCode>();
	}
	else
	{
		return nullptr;
	}
}


VertexShadingVertexCode::VertexShadingVertexCode(VERTEX_SHADING_TYPE type)
	:DefaultVertexCode(
		string(SHADER_DIRECTORY) +
		string(SHADER_VERTEXSHADING) +
		string(SHADER_EXT_VERTEX))
{
	m_Type = type;
}

void VertexShadingVertexCode::GetDefineCode(string& code)
{
	if (m_Type == VERTEX_SHADING_POSITION) {
		code += "#define VIEW_POSITION\n";
	}
	else if (m_Type == VERTEX_SHADING_COLOR) {
		code += "#define VIEW_COLOR\n";
	}
	else if (m_Type == VERTEX_SHADING_NORMAL) {
		code += "#define VIEW_NORMAL\n";
	}
	else if (m_Type == VERTEX_SHADING_TEXCOORD) {
		code += "#define VIEW_TEXCOORD\n";
	}
	else if (m_Type == VERTEX_SHADING_DEPTH) {
		code += "#define VIEW_DEPTH\n";
	}

	code += OUT_COLOR;
}

bool VertexShadingVertexCode::Compare(IShaderCode* pShaderCode)
{
	auto pVertexShadingCode = dynamic_cast<VertexShadingVertexCode*>(pShaderCode);
	if (pVertexShadingCode != nullptr)
	{
		if (m_Type == pVertexShadingCode->m_Type)
		{
			return true;
		}
	}

	return false;
}

VertexShadingFragCode::VertexShadingFragCode()
	:IShaderCode(
		string(SHADER_DIRECTORY) +
		string(SHADER_VERTEXSHADING) +
		string(SHADER_EXT_FRAG))
{
}
}
}