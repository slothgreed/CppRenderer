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
	m_uniformLocation[DEFAULT_UNIFORM_FIX_COLOR]	 = glGetUniformLocation(m_programId, "uFixColor");
	Logger::GLError();
}

void DefaultShader::Bind(shared_ptr<IUniform> uniform)
{
	if (uniform == nullptr)
	{
		return;
	}

	if (uniform->Type() == SHADER_TYPE::SHADER_TYPE_DEFAULT)
	{
		m_uniformParameter = static_pointer_cast<DefaultUniform>(uniform);
	}
	else
	{
		assert(0);
	}

	DefaultShaderDefine* pDefine = nullptr;
	if (GetShaderDefine()->Type() == SHADER_TYPE::SHADER_TYPE_DEFAULT)
	{
		pDefine = static_pointer_cast<DefaultShaderDefine>(GetShaderDefine()).get();
	}
	else
	{
		assert(0);
	}

	if (pDefine->UseColor() == false &&
		pDefine->UseNormal() == false &&
		pDefine->UseTexcoord() == false)
	{
		BindFixColor();
	}

	if (pDefine->UseTexture0() == true)
	{
		if (m_uniformParameter->GetTexture() == nullptr)
		{
			assert(0);
		}
		else
		{
			m_uniformParameter->GetTexture()->Begin();
			BindColorTexture();
		}
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

void DefaultShader::BindFixColor()
{
	if (m_uniformLocation[DEFAULT_UNIFORM_FIX_COLOR] == -1)
	{
		assert(0);
	}

	IShader::BindVector4(m_uniformLocation[DEFAULT_UNIFORM_FIX_COLOR], m_uniformParameter->FixColor());
}

void DefaultShaderDefine::GetVertexDefine(string& define)
{
	if (m_useNormal)
		define += USE_NORMAL;
	if (m_useColor)
		define += USE_COLOR;
	if (m_useTexcoord)
		define += USE_TEXCOORD;
	if (m_useGBuffer)
		define += USE_GBUFFER;
}

void DefaultShaderDefine::GetFragDefine(string& define)
{
	if (m_useTexcoord)
		define += USE_TEXCOORD;
	if (m_useTexture0)
		define += USE_TEXTURE0;
	if (m_useGBuffer)
		define += USE_GBUFFER;
}

bool DefaultShaderDefine::Compare(shared_ptr<IShaderDefine> shaderDefine)
{
	if (shaderDefine->Type() == SHADER_TYPE_DEFAULT)
	{
		DefaultShaderDefine* pDefine = (DefaultShaderDefine*)(&shaderDefine);
		if (m_useGBuffer == pDefine->m_useGBuffer &&
			m_useNormal == pDefine->m_useNormal &&
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