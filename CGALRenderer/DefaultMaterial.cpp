namespace KI
{

DefaultMaterial::DefaultMaterial()
{
}

DefaultMaterial::~DefaultMaterial()
{

}

void DefaultMaterial::AddTexture(shared_ptr<Texture> texture)
{
	m_pTexture = texture;
}
}