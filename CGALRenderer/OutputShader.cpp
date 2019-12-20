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
	m_uniformLocation.resize(OUTPUT_UNIFORM_NUM);
	m_uniformLocation[OUTPUT_UNIFORM_COLOR_TEXTURE] = glGetUniformLocation(m_programId, "uTexture0");
	Logger::GLError();

}

void OutputShader::BindOutputTexture()
{
	IShader::BindTexture(GL_TEXTURE0, m_uniformLocation[OUTPUT_UNIFORM_COLOR_TEXTURE]);
}
}
