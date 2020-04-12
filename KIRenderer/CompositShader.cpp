namespace KI
{
namespace Renderer
{
CompositShader::CompositShader()
{
}

CompositShader::~CompositShader()
{
}

void CompositShader::Initialize()
{
	FetchUniformLocation();
}

void CompositShader::FetchUniformLocation()
{
	m_uniformLocation.resize(COMPOSIT_UNIFORM_NUM);
	m_uniformLocation[COMPOSIT_UNIFORM_SOURCE_TEXTURE] = glGetUniformLocation(m_programId, "uTexture0");
	m_uniformLocation[COMPOSIT_UNIFORM_TARGET_TEXTURE] = glGetUniformLocation(m_programId, "uTexture1");
	Logger::GLError();
}

void CompositShader::Bind(shared_ptr<UniformSet> uniform)
{
	if (uniform->Frag()->Type() != SHADER_TYPE::SHADER_TYPE_COMPOSIT)
	{
		assert(0);
		return;
	}
	
	auto uniformParameter = static_pointer_cast<CompositUniform>(uniform->Frag());
}

void CompositShader::UnBind(shared_ptr<UniformSet> uniform)
{

}
}
}