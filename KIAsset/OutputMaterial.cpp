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
		assert(0);
		// need check layout;
		if (pDefaultBuffer->Layout() != (VERTEX_ATTRIB_POSITION | VERTEX_ATTRIB_TEXCOORD))
		{
			assert(0);
		}

		auto shaderDefine = make_shared<OutputShaderDefine>();
		return ShaderManager::Instance()->FindOrNew(shaderDefine);
	}
	else
	{
		assert(0);
	}

	return nullptr;
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
	m_pShader->UnBind();
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
