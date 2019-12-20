namespace KI
{
void IShader::Build(const ShaderBuildInfo& buildInfo)
{
	string vertexCode;
	string fragCode;
	FileUtility::Load(m_vertexPath, vertexCode);
	FileUtility::Load(m_fragPath, fragCode);

	vertexCode = m_version + buildInfo.vertexDefine + vertexCode;
	fragCode = m_version + buildInfo.fragDefine + fragCode;

#ifdef SHADER_DEBUG
	debug_vertexShader = vertexCode;
	debug_fragShader = fragCode;
#endif

	BuildFromCode(vertexCode, fragCode);

	m_buildInfo = buildInfo;
}

void IShader::BuildFromCode(const std::string& vertexShaderCode, const std::string& fragmentShader)
{
	GLuint vertId = ShaderUtility::Compile(vertexShaderCode, GL_VERTEX_SHADER);
	GLuint fragId = ShaderUtility::Compile(fragmentShader, GL_FRAGMENT_SHADER);

	m_programId = ShaderUtility::Link(vertId, fragId);
	Initialize();
	//UniformValidation();
}

bool IShader::UniformValidation()
{
	// defineÇ…ÇÊÇ¡ÇƒíËã`Ç≥ÇÍÇ»Ç¢uniformÇ‡Ç†ÇÈÅB
	for (int i = 0; i < m_uniformLocation.size(); i++)
	{
		if (m_uniformLocation[i] == -1)
		{
			Logger::Output(LOG_LEVEL::ERROR, "Need Call FetchUniformLocation on Initialize. And Set UniformParameter");
			return false;
		}
	}

	return true;
}

void IShader::Use()
{
	if (m_programId == 0)
	{
		Logger::Output(LOG_LEVEL::ERROR, "Not call Initialize");
	}

	glUseProgram(m_programId);
	Logger::GLError();

}

void IShader::UnUse()
{
	glUseProgram(0);
}

void IShader::Dispose()
{
	if (m_programId == 0)
	{
		glDeleteProgram(m_programId);
	}

	Logger::GLError();
}

void IShader::BindTexture(GLint activeNumber, GLint uniformId)
{
	if (m_programId == 0)
	{
		assert(0);
	}


	glActiveTexture(activeNumber);
	Logger::GLError();

	glUniform1i(uniformId, activeNumber - GL_TEXTURE0);
	Logger::GLError();
}

bool IShader::Compare(const ShaderBuildInfo& buildInfo)
{
	if (m_buildInfo.shaderType == buildInfo.shaderType &&
		m_buildInfo.vertexDefine == buildInfo.vertexDefine &&
		m_buildInfo.fragDefine == buildInfo.fragDefine) {
		return true;
	}
	else {
		return false;
	}
}
}