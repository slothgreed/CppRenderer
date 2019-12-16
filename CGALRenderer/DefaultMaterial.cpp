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
		m_pTexture->Bind();
		m_pShader->BindTexture(GL_TEXTURE0, m_pTexture->ID());
	}

}

void DefaultMaterial::UnBind()
{
	if (m_pTexture != nullptr)
	{
		m_pTexture->UnBind();
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