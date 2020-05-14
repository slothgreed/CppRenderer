
namespace KI
{
namespace Asset
{
BasicMaterialFragCode::BasicMaterialFragCode()
	:IShaderCode(string(SHADER_DIRECTORY)+
	string(SHADER_BASICMATERIAL)+
	string(SHADER_EXT_VERTEX))
{

}

BasicMaterialFragCode::~BasicMaterialFragCode()
{
}

BasicMaterial::BasicMaterial(const vec4& color)
{
	SetColor(color);
}

BasicMaterial::BasicMaterial(shared_ptr<Texture> pTexture)
{
	SetTexture(pTexture);
}

BasicMaterial::~BasicMaterial()
{
}

void BasicMaterial::SetColor(const vec4& color)
{
	m_color = color;
	m_Type = BASIC_COLOR_TYPE_FIX;
}

void BasicMaterial::SetTexture(shared_ptr<Texture> pTexture)
{
	m_pTexture = pTexture;
	m_Type = BASIC_COLOR_TYPE_TEXTURE;
}

bool BasicMaterial::ShaderDefineComare(IMaterial* pMaterial)
{
	if (pMaterial->Type() == MATERIAL_TYPE::MATERIAL_TYPE_BASIC)
	{
		auto pBasicMaterial = (BasicMaterial*)pMaterial;
		if (m_Type == pBasicMaterial->ColorType())
		{
			return true;
		}
	}

	return false;
}
}
}
