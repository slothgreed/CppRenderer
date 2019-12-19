namespace KI
{
OutputShader::OutputShader()
{
	SetVersion(GLSL_VERSION_400_CORE);
	SetVertexPath(ShaderUtility::ShaderDirectory() + "\\output.vert");
	SetFragPath(ShaderUtility::ShaderDirectory() + "\\output.frag");
}

OutputShader::~OutputShader()
{
}

void OutputShader::Initialize()
{
	FetchUniformLocation();
}


void OutputShader::FetchUniformLocation()
{
	m_uniformLocation[OUTPUT_UNIFORM_COLOR_TEXTURE] = glGetUniformLocation(m_programId, "uTexture0");
	Logger::GLError();

}

void OutputShader::BindTexture(GLint activeNumber, GLint textureId)
{
	if (m_programId == 0)
	{
		assert(0);
	}

	if (m_uniformLocation[OUTPUT_UNIFORM_COLOR_TEXTURE] == -1)
	{
		assert(0);
	}


	glActiveTexture(activeNumber);
	Logger::GLError();

	glUniform1i(m_uniformLocation[OUTPUT_UNIFORM_COLOR_TEXTURE], activeNumber - GL_TEXTURE0);
	Logger::GLError();
}
}
