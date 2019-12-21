namespace KI
{
SSLICShader::SSLICShader()
{
	SetVersion(GLSL_VERSION_400_CORE);
	SetVertexPath(ShaderUtility::ShaderDirectory() + "\\output.vert");
	SetFragPath(ShaderUtility::ShaderDirectory() + "\\output.frag");
}

SSLICShader::~SSLICShader()
{

}

void SSLICShader::Initialize()
{
	FetchUniformLocation();
}

void SSLICShader::FetchUniformLocation()
{
	m_uniformLocation.resize(SSLIC_UNIFORM_NUM);
	m_uniformLocation[SSLIC_UNIFORM_COLOR_TEXTURE] = glGetUniformLocation(m_programId, "uTexture0");

	Logger::GLError();
}

void SSLICShader::BindColorTexture()
{
	IShader::BindTexture(GL_TEXTURE0, m_uniformLocation[SSLIC_UNIFORM_COLOR_TEXTURE]);
}
}
