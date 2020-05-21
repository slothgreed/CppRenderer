namespace KI
{
namespace Gfx
{
IShaderBuildInfo::IShaderBuildInfo()
{
}

IShaderBuildInfo::~IShaderBuildInfo()
{
}

bool IShaderBuildInfo::Compare(IShaderBuildInfo* pShaderBuildInfo)
{
	if (GetVertexBuffer()->NewShaderCompare(pShaderBuildInfo->GetVertexBuffer().get()) &&
		GetShaderChunk()->NewShaderCompare(pShaderBuildInfo->GetShaderChunk().get())) {
		return true;
	}

	return false;
}

}
}