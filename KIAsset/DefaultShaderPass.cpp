namespace KI
{
namespace Asset
{
DefaultShaderPass::DefaultShaderPass()
{
}

DefaultShaderPass::~DefaultShaderPass()
{

}

void DefaultShaderPass::CompileShader(shared_ptr<IVertexBuffer> pVertexBuffer)
{
	//auto pBuildInfo = make_shared<IShaderBuildInfo>();
	//pBuildInfo->SetVertexBuffer(pVertexBuffer);
	//pBuildInfo->SetShaderChunk(make_shared<BasicShading>(vec4(1, 1, 1, 0)));
	//SetShader(ShaderManager::Instance()->FindOrNew(pBuildInfo));
}

bool DefaultShaderPass::Compare(const IShaderPass& shaderPass)
{
	if (shaderPass.Type() == SHADERPASS_TYPE_DEFAULT)
	{
		assert(0);
		// todo : compare;
	}

	return false;
}
}
}