namespace KI
{
namespace Renderer
{
OutputShader::OutputShader()
{
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

void OutputShader::Bind(shared_ptr<IUniform> uniform)
{
	if (uniform->Type() != SHADER_TYPE::SHADER_TYPE_OUTPUT)
	{
		assert(0);
	}
	else
	{
		m_uniformParameter = static_pointer_cast<OutputUniform>(uniform);
	}

	if (m_uniformParameter->pTexture == nullptr)
	{
		assert(0);
	}

	m_uniformParameter->pTexture->Begin();
	BindOutputTexture();
}

void OutputShader::UnBind()
{
	m_uniformParameter->pTexture->End();
}

void OutputShader::BindOutputTexture()
{
	IShader::BindTexture(GL_TEXTURE0, m_uniformLocation[OUTPUT_UNIFORM_COLOR_TEXTURE]);
}
}
}