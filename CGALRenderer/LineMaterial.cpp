
namespace KI
{

LineMaterial::LineMaterial()
{
	m_lineWidth = 1.0f;
}

LineMaterial::~LineMaterial()
{
}

void LineMaterial::Bind()
{
	DefaultMaterial::Bind();
	// NotSupported: on opengl4.0
	//glLineWidth(m_lineWidth);
	Logger::GLError();

}

void LineMaterial::UnBind()
{
	// NotSupported:
	//glLineWidth(1.0f);

	Logger::GLError();

	DefaultMaterial::UnBind();
}

bool LineMaterial::Compare(const IMaterial& material)
{
	if (material.Type() == MATERIAL_TYPE_LINEMATERIAL)
	{
		const LineMaterial* line = dynamic_cast<const LineMaterial*>(&material);
		if (GetLineWidth() != line->GetLineWidth())
		{
			return false;
		}
	}

	return DefaultMaterial::Compare(material);
}

}
