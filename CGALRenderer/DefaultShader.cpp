DefaultShader::DefaultShader()
{
	SetVersionPath(ShaderUtility::ShaderDirectory() + "\\version.txt");
	SetVertexPath(ShaderUtility::ShaderDirectory() + "\\default.vert");
	SetFragPath(ShaderUtility::ShaderDirectory() + "\\default.frag");
}

DefaultShader::~DefaultShader()
{
}


void DefaultShader::Initialize()
{
	BindScene();
}

void DefaultShader::BindScene()
{
	GLint sceneBlock = glGetUniformBlockIndex(m_programId, "Scene");
	glUniformBlockBinding(m_programId, sceneBlock, SCENE_DATA_LOCATION);
	Logger::GLError();
}

void DefaultShader::GetVertexShaderDefine(VERTEX_LAYOUT layout, string & shaderDefine)
{
	switch (layout)
	{
	case VERTEX_LAYOUT_P:
		break;
	case VERTEX_LAYOUT_PN:
		shaderDefine += VERTEX_SHADER_USE_NORMAL;
		break;
	case VERTEX_LAYOUT_PC:
		shaderDefine += VERTEX_SHADER_USE_COLOR;
		break;
	case VERTEX_LAYOUT_PNC:
		shaderDefine += VERTEX_SHADER_USE_NORMAL;
		shaderDefine += VERTEX_SHADER_USE_COLOR;
		break;
	case VERTEX_LAYOUT_PNCT:
		shaderDefine += VERTEX_SHADER_USE_NORMAL;
		shaderDefine += VERTEX_SHADER_USE_COLOR;
		shaderDefine += VERTEX_SHADER_USE_TEXCOORD;
		break;
	default:
		break;
	}
}
