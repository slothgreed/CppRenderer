namespace KI
{
namespace Renderer
{

Material::Material()
{
}

Material::~Material()
{
}

void Material::SetEmission(const vec4& emission)
{
	m_emission = emission;
}

void Material::SetADS(const vec4& ambient, const vec4& diffuse, const vec4& specular)
{
	m_ambient = ambient;
	m_diffuse = diffuse;
	m_specular = specular;
}

void Material::SetTexture(shared_ptr<Texture> pTexture)
{
	m_pTexture = pTexture;
}

void Material::SetNormalmap(shared_ptr<Texture> pTexture)
{
	m_pNormalmap = pTexture;
}

void Material::SetHeightmap(shared_ptr<Texture> pTexture)
{
	m_pHeightmap = pTexture;
}
}
}