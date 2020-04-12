namespace KI
{
namespace Renderer
{
SSLICShader::SSLICShader()
{
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

void SSLICShader::Bind(shared_ptr<UniformSet> pUniform)
{
	if (pUniform->Frag()->Type() != SHADER_TYPE::SHADER_TYPE_SSLIC)
	{
		assert(0);
	}
	
	auto uniformParameter = static_pointer_cast<SSLICUniform>(pUniform->Frag());
	if (uniformParameter->GetTexture() == nullptr)
	{
		assert(0);
	}

	uniformParameter->GetTexture()->Begin();
	BindColorTexture();
}

void SSLICShader::UnBind(shared_ptr<UniformSet> pUniform)
{
	if (pUniform->Frag()->Type() != SHADER_TYPE::SHADER_TYPE_SSLIC)
	{
		assert(0);
		return;
	}

	auto uniformParameter = static_pointer_cast<SSLICUniform>(pUniform->Frag());
	if (uniformParameter->GetTexture() == nullptr)
	{
		assert(0);
		return;
	}

	uniformParameter->GetTexture()->End();

}
void SSLICShader::BindColorTexture()
{
	IShader::BindTexture(GL_TEXTURE0, m_uniformLocation[SSLIC_UNIFORM_COLOR_TEXTURE]);
}
}
}