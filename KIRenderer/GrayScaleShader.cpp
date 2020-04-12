namespace KI
{
namespace Renderer
{
GrayScaleShader::GrayScaleShader()
{
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

void GrayScaleShader::Bind(shared_ptr<UniformSet> pUniform)
{
	if (pUniform->Frag()->Type() != SHADER_TYPE::SHADER_TYPE_GRAYSCALE)
	{
		assert(0);
		return;
	}

	auto uniformParameter = static_pointer_cast<GrayScaleUniform>(pUniform->Frag());
	if (uniformParameter->GetTexture() == nullptr)
	{
		assert(0);
		return;
	}

	uniformParameter->GetTexture()->Begin();
	BindColorTexture();
}

void GrayScaleShader::UnBind(shared_ptr<UniformSet> pUniform)
{
	if (pUniform->Frag()->Type() != SHADER_TYPE::SHADER_TYPE_GRAYSCALE)
	{
		assert(0);
		return;
	}

	auto uniformParameter = static_pointer_cast<GrayScaleUniform>(pUniform->Frag());
	if (uniformParameter->GetTexture() == nullptr)
	{
		assert(0);
		return;
	}

	uniformParameter->GetTexture()->End();

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