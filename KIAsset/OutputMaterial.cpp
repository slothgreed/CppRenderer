namespace KI
{
namespace Asset
{
OutputMaterial::OutputMaterial()
{
	auto pFragUniform = make_shared<OutputUniform>();
	m_pUniform = make_shared<UniformSet>(nullptr, pFragUniform);
}

OutputMaterial::~OutputMaterial()
{
}

shared_ptr<IShader> OutputMaterial::CompileShader(IVertexBuffer* pVertexBuffer)
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
		return ShaderManager::Instance()->FindOrNew(pBuildInfo);
	}
	else
	{
		assert(0);
		return nullptr;
	}
}

void OutputMaterial::AddColorTexture(shared_ptr<Texture> colorTexture)
{
	if (m_pUniform->Frag()->Type() != SHADER_TYPE::SHADER_TYPE_OUTPUT)
	{
		assert(0);
		return;
	}

	auto uniform = static_pointer_cast<OutputUniform>(m_pUniform->Frag());
	uniform->SetTexture(colorTexture);
}

void OutputMaterial::Bind()
{
	m_pShader->Bind(m_pUniform);
}

void OutputMaterial::UnBind()
{
	m_pShader->UnBind(m_pUniform);
}

bool OutputMaterial::Compare(const IMaterial& material)
{
	if (material.Type() == MATERIAL_TYPE_OUTPUT_BUFFER)
	{
		return true;
	}

	return false;
}
}
}
