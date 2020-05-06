namespace KI
{
namespace Asset
{

GeneralShaderPass::GeneralShaderPass()
{
}

GeneralShaderPass::~GeneralShaderPass()
{
}

void GeneralShaderPass::CompileShader(IVertexBuffer* pVertexBuffer)
{
	assert(0);
}

bool GeneralShaderPass::Compare(const IShaderPass& material)
{
	return false;
}
}
}