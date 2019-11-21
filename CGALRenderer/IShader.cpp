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

	BuildFromCode(vertexCode, fragCode);

	m_buildInfo = buildInfo;
}

void IShader::BuildFromCode(const std::string& vertexShaderCode, const std::string& fragmentShader)
{
	GLuint vertId = ShaderUtility::Compile(vertexShaderCode, GL_VERTEX_SHADER);
	GLuint fragId = ShaderUtility::Compile(fragmentShader, GL_FRAGMENT_SHADER);

	m_programId = ShaderUtility::Link(vertId, fragId);
	Initialize();
}


void IShader::Use()
{
	if (m_programId == 0)
	{
		Logger::Output(LOG_LEVEL::ERROR, "Not call Initialize");
	}

	glUseProgram(m_programId);
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