
namespace KI
{
namespace Renderer
{

#define FRAG_SHADER_COMPOSIT_ADD		"#define COMPOSIT_ADD\n"
#define FRAG_SHADER_COMPOSIT_SUB		"#define COMPOSIT_SUB\n"
#define FRAG_SHADER_COMPOSIT_MULT		"#define COMPOSIT_MULT\n"
#define FRAG_SHADER_COMPOSIT_OVERWRITE	"#define COMPOSIT_OVERWRITE\n"

void CompositFragCode::SetShaderDefine(CompositFragCode::COMPOSIT_TYPE type)
{
	m_CompositType = type;
}

void CompositFragCode::GetDefineCode(string& code)
{
	switch (m_CompositType)
	{
	case CompositFragCode::COMPOSIT_TYPE_ADD:
		code += FRAG_SHADER_COMPOSIT_ADD;
		break;
	case CompositFragCode::COMPOSIT_TYPE_SUB:
		code += FRAG_SHADER_COMPOSIT_SUB;
		break;
	case CompositFragCode::COMPOSIT_TYPE_MULT:
		code += FRAG_SHADER_COMPOSIT_MULT;
		break;
	case CompositFragCode::COMPOSIT_TYPE_OVERWRITE:
		code += FRAG_SHADER_COMPOSIT_ADD;
		break;
	case CompositFragCode::COMPOSIT_TYPE_NUM:
		code += FRAG_SHADER_COMPOSIT_OVERWRITE;
		break;
	default:
		assert(0);
		break;
	}
}

bool CompositFragCode::Compare(IShaderCode* pShaderCode)
{
	if (pShaderCode->Type() == SHADER_TYPE::SHADER_TYPE_COMPOSIT)
	{
		CompositFragCode* pDefine = (CompositFragCode*)(pShaderCode);
		if (m_CompositType == pDefine->m_CompositType)
		{
			return true;
		}
	}

	return false;
}
}
}