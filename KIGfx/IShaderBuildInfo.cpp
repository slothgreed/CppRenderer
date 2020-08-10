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
	bool vertexCompare = false;
	bool chunkCompare = false;
	if (GetVertexBuffer() != NULL && pShaderBuildInfo->GetVertexBuffer() != NULL) {
		if (GetVertexBuffer()->NewShaderCompare(pShaderBuildInfo->GetVertexBuffer().get())) {
			vertexCompare = true;
		}
	}

	if (GetVertexBuffer() == NULL && pShaderBuildInfo->GetVertexBuffer() == NULL)
	{
		vertexCompare = true;
	}
	

	if (GetShaderChunk() != NULL && pShaderBuildInfo->GetShaderChunk() != NULL) {
		if (GetShaderChunk()->NewShaderCompare(pShaderBuildInfo->GetShaderChunk().get())) {
			chunkCompare = true;
		}
	}

	if (GetShaderChunk() == NULL && pShaderBuildInfo->GetShaderChunk() == NULL) {
		chunkCompare = true;
	}

	return vertexCompare && chunkCompare;
}

}
}