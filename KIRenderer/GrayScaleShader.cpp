namespace KI
{
namespace Renderer
{
GrayScaleShader::GrayScaleShader()
{
	SetVersion(GLSL_VERSION_400_CORE);
	SetVertexPath(string(SHADER_DIRECTORY) + "\\postprocess.vert");
	SetFragPath(string(SHADER_DIRECTORY) + "\\grayscale.frag");
}

GrayScaleShader::~GrayScaleShader()
{
}
void GrayScaleShader::Initialize()
{
	FetchUniformLocation();
}

void GrayScaleShader::FetchUniformLocation()
{
	m_uniformLocation.resize(GRAYSCALE_UNIFORM_NUM);
	m_uniformLocation[GRAYSCALE_UNIFORM_SOURCE_TEXTURE] = glGetUniformLocation(m_programId, "uTexture0");
	Logger::GLError();
}

void GrayScaleShader::Bind(shared_ptr<IUniform> uniform)
{
	if (uniform->Type() != SHADER_TYPE::SHADER_TYPE_GRAYSCALE)
	{
		assert(0);
	}
	else
	{
		m_uniformParameter = static_pointer_cast<GrayScaleUniform>(uniform);
	}

	if (m_uniformParameter->pTexture == nullptr)
	{
		assert(0);
	}

	m_uniformParameter->pTexture->Begin();
	BindColorTexture();
}

void GrayScaleShader::UnBind()
{
	if (m_uniformParameter->pTexture == nullptr)
	{
		assert(0);
	}

	m_uniformParameter->pTexture->End();

}

void GrayScaleShader::BindColorTexture()
{
	if (m_uniformLocation[GRAYSCALE_UNIFORM_SOURCE_TEXTURE] == -1)
	{
		assert(0);
	}

	IShader::BindTexture(GL_TEXTURE0, m_uniformLocation[GRAYSCALE_UNIFORM_SOURCE_TEXTURE]);
}
}
}