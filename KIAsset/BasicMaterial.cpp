
namespace KI
{
namespace Asset
{

BasicMaterial::BasicMaterial(const vec4& color)
{
	SetColor(color);
}

BasicMaterial::BasicMaterial(shared_ptr<Texture> pTexture)
{
	SetTexture(pTexture);
}

BasicMaterial::BasicMaterial(BASIC_COLOR_TYPE type)
{
	if (type == BASIC_COLOR_TYPE_FIX ||
		type == BASIC_COLOR_TYPE_TEXTURE)
	{
		assert(0);
		SetColor(vec4(1, 1, 0, 1));
	}
	else
	{
		m_Type = type;
	}
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

}
}
