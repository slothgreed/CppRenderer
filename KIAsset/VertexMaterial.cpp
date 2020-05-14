namespace KI
{
namespace Asset
{

VertexMaterial::VertexMaterial(VERTEX_MATERIAL_TYPE type)
{
	m_Type = type;
}

VertexMaterial::~VertexMaterial()
{
}

bool VertexMaterial::ShaderDefineComare(IMaterial* pMaterial)
{
	if (pMaterial->Type() == MATERIAL_TYPE::MATERIAL_TYPE_VERTEX)
	{
		auto pVertexMaterial = (VertexMaterial*)pMaterial;
		if (m_Type == pVertexMaterial->ColorType())
		{
			return true;
		}
	}

	return false;
}

}
}
