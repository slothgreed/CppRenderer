namespace KI
{
namespace Renderer
{

ADSMaterial::ADSMaterial()
{
}

void ADSMaterial::Set(const vec4& ambient, const vec4& diffuse, const vec4& specular, float shinness) 
{
	m_ambient = ambient;
	m_diffuse = diffuse;
	m_specular = specular;
	m_shinness = shinness;
}

shared_ptr<IShaderCode> ADSMaterial::NewShaderCode(IShaderBuildInfo* pBuildInfo,SHADER_PROGRAM_TYPE type)
{
	assert(0);
	return false;
}
}
}