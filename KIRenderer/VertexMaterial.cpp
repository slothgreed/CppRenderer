
namespace KI
{
namespace Renderer
{

VertexMaterial::VertexMaterial(VERTEX_MATERIAL_TYPE type)
{
	m_Type = type;
}

VertexMaterial::~VertexMaterial()
{
}

bool VertexMaterial::Compare(IMaterial* pMaterial)
{
	auto pVertexMaterial = dynamic_cast<VertexMaterial*>(pMaterial);
	if (m_Type == pVertexMaterial->Type())
	{
		return true;
	}

	return false;
}

bool VertexMaterial::NewShaderCompare(IShaderChunk* pTarget)
{
	auto pVertexMaterial = dynamic_cast<VertexMaterial*>(pTarget);
	
	return Compare(pVertexMaterial);
}

shared_ptr<IShaderCode> VertexMaterial::NewShaderCode(IShaderBuildInfo* pBuildInfo,SHADER_PROGRAM_TYPE type)
{
	if (type == SHADER_PROGRAM_VERTEX) {
		return make_shared<VertexMaterialVertexCode>(m_Type);
	}
	else if (type == SHADER_PROGRAM_VERTEX)
	{
		return make_shared<VertexMaterialFragCode>();
	}
	else
	{
		return nullptr;
	}
}


VertexMaterialVertexCode::VertexMaterialVertexCode(VERTEX_MATERIAL_TYPE type)
	:DefaultVertexCode(
		string(SHADER_DIRECTORY) +
		string(SHADER_VERTEXMATERIAL) +
		string(SHADER_EXT_VERTEX))
{
	m_Type = type;
}

void VertexMaterialVertexCode::GetDefineCode(string& code)
{
	if (m_Type == VERTEX_MATERIAL_POSITION) {
		code += "#define VIEW_POSITION\n";
	}
	else if (m_Type == VERTEX_MATERIAL_COLOR) {
		code += "#define VIEW_COLOR\n";
	}
	else if (m_Type == VERTEX_MATERIAL_NORMAL) {
		code += "#define VIEW_NORMAL\n";
	}
	else if (m_Type == VERTEX_MATERIAL_TEXCOORD) {
		code += "#define VIEW_TEXCOORD\n";
	}
	else if (m_Type == VERTEX_MATERIAL_DEPTH) {
		code += "#define VIEW_DEPTH\n";
	}

	code += OUT_COLOR;
}

bool VertexMaterialVertexCode::Compare(IShaderCode* pShaderCode)
{
	auto pVertexMaterialCode = dynamic_cast<VertexMaterialVertexCode*>(pShaderCode);
	if (pVertexMaterialCode != nullptr)
	{
		if (m_Type == pVertexMaterialCode->m_Type)
		{
			return true;
		}
	}

	return false;
}

VertexMaterialFragCode::VertexMaterialFragCode()
	:IShaderCode(
		string(SHADER_DIRECTORY) +
		string(SHADER_VERTEXMATERIAL) +
		string(SHADER_EXT_FRAG))
{
}
}
}