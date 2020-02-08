namespace KI
{

DefaultShader::DefaultShader()
{
	SetVersion(GLSL_VERSION_400_CORE);
	SetVertexPath(ShaderUtility::ShaderDirectory() + "\\default.vert");
	SetFragPath(ShaderUtility::ShaderDirectory() + "\\default.frag");
}

DefaultShader::~DefaultShader()
{
}

void DefaultShader::Initialize()
{
	BindScene();
	FetchUniformLocation();
}

void DefaultShader::BindScene()
{
	GLint sceneBlock = glGetUniformBlockIndex(m_programId, "Scene");
	glUniformBlockBinding(m_programId, sceneBlock, SCENE_DATA_LOCATION);
	Logger::GLError();
}

void DefaultShader::FetchUniformLocation()
{
	m_uniformLocation.resize(DEFAULT_UNIFORM_NUM);
	m_uniformLocation[DEFAULT_UNIFORM_COLOR_TEXTURE] = glGetUniformLocation(m_programId, "uTexture0");

	Logger::GLError();
}

void DefaultShader::Bind(shared_ptr<IUniform> uniform)
{
	if (uniform == nullptr)
	{
		return;
	}

	if (uniform->Type() != SHADER_TYPE::SHADER_TYPE_DEFAULT)
	{
		assert(0);
	}
	else
	{
		m_uniformParameter = static_pointer_cast<DefaultUniform>(uniform);
	}

	if (m_uniformParameter->GetTexture() != nullptr)
	{
		m_uniformParameter->GetTexture()->Begin();
		BindColorTexture();
	}

}

void DefaultShader::UnBind()
{
	if (m_uniformParameter == nullptr)
	{
		return;
	}

	if (m_uniformParameter->GetTexture() != nullptr)
	{
		m_uniformParameter->GetTexture()->End();
	}
}

void DefaultShader::BindColorTexture()
{
	if (m_uniformLocation[DEFAULT_UNIFORM_COLOR_TEXTURE] == -1)
	{
		assert(0);
	}

	IShader::BindTexture(GL_TEXTURE0, m_uniformLocation[DEFAULT_UNIFORM_COLOR_TEXTURE]);
}

void DefaultShaderDefine::GetVertexDefine(string& define)
{
	if (m_useNormal)
		define += VERTEX_SHADER_USE_NORMAL;

	if (m_useColor)
		define += VERTEX_SHADER_USE_COLOR;

	if (m_useTexcoord)
		define += VERTEX_SHADER_USE_TEXCOORD;
}

void DefaultShaderDefine::GetFragDefine(string& define)
{
	if (m_useTexcoord)
		define += VERTEX_SHADER_USE_TEXCOORD;
	if (m_useTexture0)
		define += FRAG_SHADER_USE_TEXTURE0;
}

bool DefaultShaderDefine::Compare(shared_ptr<IShaderDefine> shaderDefine)
{
	if (shaderDefine->Type() == SHADER_TYPE_DEFAULT)
	{
		DefaultShaderDefine* pDefine = (DefaultShaderDefine*)(&shaderDefine);
		if (m_useNormal == pDefine->m_useNormal &&
			m_useColor == pDefine->m_useColor &&
			m_useTexcoord == pDefine->m_useTexcoord &&
			m_useTexture0 == pDefine->m_useTexture0)
		{
			return true;
		}
	}

	return false;
}

void DefaultShaderDefine::SetShaderDefine(VERTEX_LAYOUT layout)
{
	switch (layout)
	{
	case VERTEX_LAYOUT_P:
		break;
	case VERTEX_LAYOUT_PN:
		m_useNormal = true;
		break;
	case VERTEX_LAYOUT_PC:
		m_useColor = true;
		break;
	case VERTEX_LAYOUT_PT:
		m_useTexcoord = true;
		m_useTexture0 = true;
		break;
	case VERTEX_LAYOUT_PNC:
		m_useNormal = true;
		m_useColor = true;
		break;
	case VERTEX_LAYOUT_PNCT:
		m_useNormal = true;
		m_useColor = true;
		m_useTexcoord = true;
		m_useTexture0 = true;
		break;
	default:
		break;
	}
}

}