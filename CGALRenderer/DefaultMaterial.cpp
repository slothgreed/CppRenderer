namespace KI
{

DefaultMaterial::DefaultMaterial()
{
}

DefaultMaterial::~DefaultMaterial()
{

}

void DefaultMaterial::AddTexture(shared_ptr<Texture> texture)
{
	m_pTexture = texture;
}

void DefaultMaterial::CompileShader()
{
	if (m_pVertexBuffer->Type() == DefaultVertexBuffer::DefaultVertexBufferTypeStr)
	{
		auto pDefaultBuffer = static_pointer_cast<DefaultVertexBuffer>(m_pVertexBuffer);
		ShaderBuildInfo shaderInfo;
		DefaultShader::GetVertexShaderDefine(pDefaultBuffer->Layout(), shaderInfo);
		DefaultShader::GetFragShaderDefine(pDefaultBuffer->Layout(), shaderInfo);
		m_pShader = ShaderManager::Instance()->FindOrNew(shaderInfo);
	}
	else
	{
		assert(0);
	}
}

void DefaultMaterial::Bind()
{
	if (m_pTexture != nullptr)
	{
		if (m_pShader->Type() == SHADER_TYPE::SHADER_TYPE_DEFAULT)
		{
			auto pOutputShader = static_pointer_cast<DefaultShader>(m_pShader);
			m_pTexture->Begin();
			pOutputShader->BindColorTexture();
		}
	}

}

void DefaultMaterial::UnBind()
{
	if (m_pTexture != nullptr)
	{
		m_pTexture->End();
	}
}

bool DefaultMaterial::Compare(const IMaterial& material)
{
	if (material.Type() == MATERIAL_TYPE_DEFAULT)
	{
		assert(0);
		// todo : compare;
	}

	return false;
}
}