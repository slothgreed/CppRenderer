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
		m_pShader = ShaderManager::Instance()->FindOrNew(shaderInfo);
	}
	else
	{
		assert(0);
	}
}

void DefaultMaterial::Draw()
{
	if (m_pShader == nullptr ||
		m_pVertexBuffer == nullptr)
	{
		assert(0);
	}

	Bind();
	m_pShader->Use();
	m_pVertexBuffer->Draw();
	m_pShader->UnUse();
	UnBind();
}
}