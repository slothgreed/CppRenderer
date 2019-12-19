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

void DefaultShader::BindColorTexture()
{
	if (m_uniformLocation[DEFAULT_UNIFORM_COLOR_TEXTURE] == -1)
	{
		assert(0);
	}

	IShader::BindTexture(GL_TEXTURE0, m_uniformLocation[DEFAULT_UNIFORM_COLOR_TEXTURE]);
}

void DefaultShader::GetVertexShaderDefine(VERTEX_LAYOUT layout, ShaderBuildInfo& shaderDefine)
{
	shaderDefine.shaderType = SHADER_TYPE::SHADER_TYPE_DEFAULT;
	switch (layout)
	{
	case VERTEX_LAYOUT_P:
		break;
	case VERTEX_LAYOUT_PN:
		shaderDefine.vertexDefine += VERTEX_SHADER_USE_NORMAL;
		break;
	case VERTEX_LAYOUT_PC:
		shaderDefine.vertexDefine += VERTEX_SHADER_USE_COLOR;
		break;
	case VERTEX_LAYOUT_PT:
		shaderDefine.vertexDefine += VERTEX_SHADER_USE_TEXCOORD;
		break;
	case VERTEX_LAYOUT_PNC:
		shaderDefine.vertexDefine += VERTEX_SHADER_USE_NORMAL;
		shaderDefine.vertexDefine += VERTEX_SHADER_USE_COLOR;
		break;
	case VERTEX_LAYOUT_PNCT:
		shaderDefine.vertexDefine += VERTEX_SHADER_USE_NORMAL;
		shaderDefine.vertexDefine += VERTEX_SHADER_USE_COLOR;
		shaderDefine.vertexDefine += VERTEX_SHADER_USE_TEXCOORD;
		break;
	default:
		break;
	}
}

void DefaultShader::GetFragShaderDefine(VERTEX_LAYOUT layout, ShaderBuildInfo& shaderDefine)
{
	shaderDefine.shaderType = SHADER_TYPE::SHADER_TYPE_DEFAULT;
	switch (layout)
	{
	case VERTEX_LAYOUT_PT:
	case VERTEX_LAYOUT_PNCT:
		shaderDefine.fragDefine += FRAG_SHADER_USE_TECOORD;
		shaderDefine.fragDefine += FRAG_SHADER_USE_TEXTURE0;
		break;
	default:
		break;
	}
}
}