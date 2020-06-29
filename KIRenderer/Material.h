namespace KI
{
namespace Renderer
{

class Material
{
public:
	Material();
	~Material();

	void SetEmission(const vec4& emission);
	void SetADS(const vec4& ambient, const vec4& diffuse, const vec4& specular);
	void SetTexture(shared_ptr<Texture> pTexture);
	void SetNormalmap(shared_ptr<Texture> pTexture);
	void SetHeightmap(shared_ptr<Texture> pTexture);
private:

	vec4 m_ambient;
	vec4 m_diffuse;
	vec4 m_specular;
	vec4 m_emission;

	shared_ptr<Texture> m_pTexture;
	shared_ptr<Texture> m_pNormalmap;
	shared_ptr<Texture> m_pHeightmap;
};
}
}