namespace KI
{

OutputMaterial::OutputMaterial()
{
}

OutputMaterial::~OutputMaterial()
{
}

void OutputMaterial::CompileShader()
{
	if (m_pVertexBuffer->Type() == DefaultVertexBuffer::DefaultVertexBufferTypeStr)
	{
		auto pDefaultBuffer = static_pointer_cast<DefaultVertexBuffer>(m_pVertexBuffer);
		ShaderBuildInfo shaderInfo;
		shaderInfo.shaderType = SHADER_TYPE::SHADER_TYPE_OUTPUT;
		if (pDefaultBuffer->Layout() != VERTEX_LAYOUT::VERTEX_LAYOUT_PT)
		{
			assert(0);
		}


		m_pShader = ShaderManager::Instance()->FindOrNew(shaderInfo);
	}
	else
	{
		assert(0);
	}
}

void OutputMaterial::AddColorTexture(shared_ptr<Texture> colorTexture)
{
	m_pColorTexture = colorTexture;
}

void OutputMaterial::Bind()
{
	if (m_pColorTexture == nullptr)
	{
		assert(0);
	}
	else
	{
		if (m_pShader->Type() == SHADER_TYPE::SHADER_TYPE_OUTPUT)
		{
			auto pOutputShader = static_pointer_cast<OutputShader>(m_pShader);
			m_pColorTexture->Begin();
			pOutputShader->BindOutputTexture();
		}
	}
}

void OutputMaterial::UnBind()
{
	if (m_pColorTexture != nullptr)
	{
		m_pColorTexture->End();
	}
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