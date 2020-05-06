namespace KI
{
namespace Asset
{

GeneralPass::GeneralPass()
{
}

GeneralPass::~GeneralPass()
{
}

void GeneralPass::CompileShader(IVertexBuffer* pVertexBuffer)
{
	assert(0);
}

bool GeneralPass::Compare(const IShaderPass& material)
{
	return false;
}
}
}