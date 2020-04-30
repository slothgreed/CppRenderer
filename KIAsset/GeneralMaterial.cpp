namespace KI
{
namespace Asset
{

GeneralMaterial::GeneralMaterial()
{
}

GeneralMaterial::~GeneralMaterial()
{
}

void GeneralMaterial::CompileShader(IVertexBuffer* pVertexBuffer)
{
	assert(0);
}

bool GeneralMaterial::Compare(const IMaterial& material)
{
	return false;
}
}
}