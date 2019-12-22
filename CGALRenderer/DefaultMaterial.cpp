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
	if (m_pUniform == nullptr)
	{
		m_pUniform = make_shared<DefaultUniform>();
	}
	m_pUniform->pTexture = texture;
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
	m_pShader->Bind(m_pUniform);
}

void DefaultMaterial::UnBind()
{
	m_pShader->UnBind();
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