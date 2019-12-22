namespace KI
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

void CompositShader::GetFragShaderDefine(COMPOSIT_TYPE type, ShaderBuildInfo& shaderDefine)
{
	shaderDefine.shaderType = SHADER_TYPE::SHADER_TYPE_DEFAULT;
	switch (type)
	{
	case COMPOSIT_TYPE_ADD:
		shaderDefine.fragDefine += FRAG_SHADER_COMPOSIT_ADD;
		break;
	case COMPOSIT_TYPE_SUB:
		shaderDefine.fragDefine += FRAG_SHADER_COMPOSIT_SUB; 
		break;
	case COMPOSIT_TYPE_MULT:
		shaderDefine.fragDefine += FRAG_SHADER_COMPOSIT_MULT; 
		break;
	case COMPOSIT_TYPE_OVERWRITE:
		shaderDefine.fragDefine += FRAG_SHADER_COMPOSIT_OVERWRITE; 
		break;
	default:
		assert(0);
		break;
	}
}
}
