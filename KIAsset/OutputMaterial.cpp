namespace KI
{
namespace Asset
{
OutputMaterial::OutputMaterial()
{
	m_pUniform = make_shared<OutputUniform>();
}

OutputMaterial::~OutputMaterial()
{
}

shared_ptr<IShader> OutputMaterial::CompileShader(IVertexBuffer* pVertexBuffer)
{
	if (pVertexBuffer->Type() == SHADER_TYPE::SHADER_TYPE_DEFAULT)
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
	m_pUniform->pTexture = colorTexture;
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
