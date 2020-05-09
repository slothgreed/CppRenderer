namespace KI
{
namespace Asset
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
}
}