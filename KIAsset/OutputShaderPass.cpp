namespace KI
{
namespace Asset
{
OutputShaderPass::OutputShaderPass()
{
	auto pFragUniform = make_shared<OutputUniform>();
	GetUniform()->Set(nullptr, pFragUniform);

}

OutputShaderPass::~OutputShaderPass()
{
}

void OutputShaderPass::CompileShader(IVertexBuffer* pVertexBuffer)
{
	if (pVertexBuffer->Type() == VERTEX_BUFFER_TYPE_DEFAULT)
	{
		auto pDefaultBuffer = (DefaultVertexBuffer*)(pVertexBuffer);
		if (pDefaultBuffer->Layout() != (VERTEX_LAYOUT_POSITION | VERTEX_LAYOUT_TEXCOORD))
		{
			assert(0);
		}

		auto pBuildInfo = make_shared<IShaderBuildInfo>(SHADER_TYPE_OUTPUT);
		pBuildInfo->SetVertexCode(make_shared<PostProcessVertexCode>());
		pBuildInfo->SetFragCode(make_shared<OutputFragCode>());
		SetShader(ShaderManager::Instance()->FindOrNew(pBuildInfo));
	}
	else
	{
		assert(0);
	}
}

void OutputShaderPass::AddColorTexture(shared_ptr<Texture> colorTexture)
{
	if (GetUniform()->Frag()->Type() != SHADER_TYPE::SHADER_TYPE_OUTPUT)
	{
		assert(0);
		return;
	}

	auto uniform = static_pointer_cast<OutputUniform>(GetUniform()->Frag());
	uniform->SetTexture(colorTexture);
}

bool OutputShaderPass::Compare(const IShaderPass& shaderPass)
{
	if (shaderPass.Type() == SHADERPASS_TYPE_OUTPUT_BUFFER)
	{
		return true;
	}

	return false;
}
}
}
