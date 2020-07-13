namespace KI
{
namespace ShaderLib
{
CompositFragCode::CompositFragCode(COMPOSIT_TYPE type)
	:IShaderCode(
		string(SHADER_DIRECTORY) +
		string(SHADER_OUTPUT) +
		string(SHADER_EXT_FRAG))
{
	m_CompositType = type;
}

CompositFragCode::~CompositFragCode()
{
}

void CompositFragCode::GetDefineCode(string& code)
{
	switch (m_CompositType)
	{
	case COMPOSIT_TYPE::COMPOSIT_TYPE_ADD:
		code += "#define COMPOSIT_ADD\n";
		break;
	case COMPOSIT_TYPE::COMPOSIT_TYPE_SUB:
		code += "#define COMPOSIT_SUB\n";
		break;
	case COMPOSIT_TYPE::COMPOSIT_TYPE_MULT:
		code += "#define COMPOSIT_MULT\n";
		break;
	case COMPOSIT_TYPE::COMPOSIT_TYPE_OVERWRITE:
		code += "#define COMPOSIT_OVERWRITE\n";
		break;
	default:
		assert(0);
		break;
	}
}

bool CompositFragCode::Compare(IShaderCode* pShaderCode)
{
	auto pCode = dynamic_cast<CompositFragCode*>(pShaderCode);
	if (pCode == nullptr)
	{
		return false;
	}

	if (m_CompositType == pCode->m_CompositType)
	{
		return true;
	}

	return false;
}
void CompositFragCode::Initialize(GLuint programId)
{
	m_uniformLocation.resize(COMPOSIT_UNIFORM_NUM);
	m_uniformLocation[COMPOSIT_UNIFORM_SOURCE_TEXTURE] = glGetUniformLocation(programId, "uTexture0");
	m_uniformLocation[COMPOSIT_UNIFORM_TARGET_TEXTURE] = glGetUniformLocation(programId, "uTexture1");
	Logger::GLError();
}

void CompositFragCode::Bind(shared_ptr<IShaderChunk> pShaderChunk,shared_ptr<IUniformStorage> pUniform)
{
	auto pShading = static_pointer_cast<CompositShading>(pShaderChunk);
	{
		assert(0);
		return;
	}

	pShading->GetSource()->Begin();
	pShading->GetDestination()->Begin();
	IShaderCode::BindTexture(GL_TEXTURE0, m_uniformLocation[COMPOSIT_UNIFORM_SOURCE_TEXTURE]);
	IShaderCode::BindTexture(GL_TEXTURE1, m_uniformLocation[COMPOSIT_UNIFORM_TARGET_TEXTURE]);
}

void CompositFragCode::UnBind(shared_ptr<IShaderChunk> pShaderChunk,shared_ptr<IUniformStorage> pUniform)
{
	auto pShading = static_pointer_cast<CompositShading>(pShaderChunk);
	{
		assert(0);
		return;
	}

	pShading->GetSource()->End();
	pShading->GetDestination()->End();
}

shared_ptr<IShaderCode> CompositShading::NewShaderCode(IShaderBuildInfo* pBuildInfo,SHADER_PROGRAM_TYPE type)
{
	if (type == SHADER_PROGRAM_VERTEX)
	{
		return make_shared<DefaultVertexCode>(pBuildInfo->GetVertexBuffer().get());
	}
	else if (type == SHADER_PROGRAM_FRAG)
	{
		return make_shared<CompositFragCode>(m_Type);
	}
	else
	{
		return nullptr;
	}
}
}
}