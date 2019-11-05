void IShader::Build(const ShaderBuildInfo& buildInfo)
{
	string vertexCode;
	string fragCode;
	string version;
	FileIO::Load(m_versionPath, version);
	FileIO::Load(m_vertexPath, vertexCode);
	FileIO::Load(m_fragPath, fragCode);

	vertexCode = version + buildInfo.vertexDefine + vertexCode;
	fragCode = version + buildInfo.fragDefine + fragCode;

	BuildFromCode(vertexCode, fragCode);
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