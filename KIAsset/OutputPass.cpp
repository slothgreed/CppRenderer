namespace KI
{
namespace Asset
{
OutputPass::OutputPass()
{
	auto pFragUniform = make_shared<OutputUniform>();
	GetUniform()->Set(nullptr, pFragUniform);

}

OutputPass::~OutputPass()
{
}

void OutputPass::CompileShader(IVertexBuffer* pVertexBuffer)
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

void OutputPass::AddColorTexture(shared_ptr<Texture> colorTexture)
{
	if (GetUniform()->Frag()->Type() != SHADER_TYPE::SHADER_TYPE_OUTPUT)
	{
		assert(0);
		return;
	}

	auto uniform = static_pointer_cast<OutputUniform>(GetUniform()->Frag());
	uniform->SetTexture(colorTexture);
}

bool OutputPass::Compare(const IShaderPass& material)
{
	if (material.Type() == MATERIAL_TYPE_OUTPUT_BUFFER)
	{
		return true;
	}

	return false;
}
}
}
