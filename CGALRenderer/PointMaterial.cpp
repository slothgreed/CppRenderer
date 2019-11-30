namespace KI
{
PointMaterial::PointMaterial()
{
}

PointMaterial::~PointMaterial()
{
}

void PointMaterial::Bind()
{
	DefaultMaterial::Bind();

	glPointSize(m_pointSize);
}

void PointMaterial::UnBind()
{
	glPointSize(1.0f);
	DefaultMaterial::UnBind();

}
bool PointMaterial::Compare(const IMaterial& material)
{
	if (material.Type() == MATERIAL_TYPE_POINTMATERIAL)
	{
		const PointMaterial* point = dynamic_cast<const PointMaterial*>(&material);
		if (GetPointSize() != point->GetPointSize())
		{
			return false;
		}
	}

	return DefaultMaterial::Compare(material);
}
}
