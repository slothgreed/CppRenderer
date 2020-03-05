namespace KI
{
namespace Renderer
{
CompositShader::CompositShader()
{
	SetVersion(GLSL_VERSION_400_CORE);
	SetVertexPath(ShaderUtility::ShaderDirectory() + "\\composit.vert");
	SetFragPath(ShaderUtility::ShaderDirectory() + "\\composit.frag");
}

CompositShader::~CompositShader()
{
}

void CompositShader::Initialize()
{
	FetchUniformLocation();
}

void CompositShader::FetchUniformLocation()
{
	m_uniformLocation.resize(COMPOSIT_UNIFORM_NUM);
	m_uniformLocation[COMPOSIT_UNIFORM_SOURCE_TEXTURE] = glGetUniformLocation(m_programId, "uTexture0");
	m_uniformLocation[COMPOSIT_UNIFORM_TARGET_TEXTURE] = glGetUniformLocation(m_programId, "uTexture1");
	Logger::GLError();
}

void CompositShader::Bind(shared_ptr<IUniform> uniform)
{
	if (uniform->Type() != SHADER_TYPE::SHADER_TYPE_COMPOSIT)
	{
		assert(0);
	}
	else
	{
		m_uniformParameter = static_pointer_cast<CompositUniform>(uniform);
	}
}

void CompositShader::UnBind()
{

}
void CompositShaderDefine::SetShaderDefine(CompositShader::COMPOSIT_TYPE type)
{
	m_CompositType = type;
}
bool CompositShaderDefine::Compare(IShaderDefine* shaderDefine)
{
	if (shaderDefine->Type() == SHADER_TYPE::SHADER_TYPE_COMPOSIT)
	{
		CompositShaderDefine* pDefine = (CompositShaderDefine*)(shaderDefine);
		if (m_CompositType == pDefine->m_CompositType)
		{
			return true;
		}
	}

	return false;
}
void CompositShaderDefine::GetFragDefine(string& define)
{
	switch (m_CompositType)
	{
	case CompositShader::COMPOSIT_TYPE_ADD:
		define += FRAG_SHADER_COMPOSIT_ADD;
		break;
	case CompositShader::COMPOSIT_TYPE_SUB:
		define += FRAG_SHADER_COMPOSIT_SUB;
		break;
	case CompositShader::COMPOSIT_TYPE_MULT:
		define += FRAG_SHADER_COMPOSIT_MULT;
		break;
	case CompositShader::COMPOSIT_TYPE_OVERWRITE:
		define += FRAG_SHADER_COMPOSIT_ADD;
		break;
	case CompositShader::COMPOSIT_TYPE_NUM:
		define += FRAG_SHADER_COMPOSIT_OVERWRITE;
		break;
	default:
		assert(0);
		break;
	}
}
}
}