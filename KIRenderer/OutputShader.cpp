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

void OutputShader::Bind(shared_ptr<UniformSet> pUniform)
{
	if (pUniform->Frag()->Type() != SHADER_TYPE::SHADER_TYPE_OUTPUT)
	{
		assert(0);
		return;
	}

	auto uniformParameter = static_pointer_cast<OutputUniform>(pUniform->Frag());
	if (uniformParameter->GetTexture() == nullptr)
	{
		assert(0);
		return;
	}

	uniformParameter->GetTexture()->Begin();
	BindOutputTexture();
}

void OutputShader::UnBind(shared_ptr<UniformSet> pUniform)
{
	if (pUniform->Frag()->Type() != SHADER_TYPE::SHADER_TYPE_OUTPUT)
	{
		assert(0);
		return;
	}

	auto uniformParameter = static_pointer_cast<OutputUniform>(pUniform->Frag());
	if (uniformParameter->GetTexture() == nullptr)
	{
		assert(0);
		return;
	}

	uniformParameter->GetTexture()->End();
}

void OutputShader::BindOutputTexture()
{
	IShader::BindTexture(GL_TEXTURE0, m_uniformLocation[OUTPUT_UNIFORM_COLOR_TEXTURE]);
}
}
}