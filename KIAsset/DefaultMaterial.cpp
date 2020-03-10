namespace KI
{
namespace Asset
{
DefaultMaterial::DefaultMaterial()
{
	m_pUniform = make_shared<DefaultUniform>();
}

DefaultMaterial::~DefaultMaterial()
{

}

void DefaultMaterial::AddTexture(shared_ptr<Texture> texture)
{
	m_pUniform->SetTexture(texture);
}

void DefaultMaterial::SetFixColor(vec4 color)
{
	m_pUniform->SetFixColor(color);
}

shared_ptr<IShader> DefaultMaterial::CompileShader(IVertexBuffer* pVertexBuffer)
{
	if (pVertexBuffer->Type() == SHADER_TYPE::SHADER_TYPE_DEFAULT)
	{
		auto pDefaultBuffer = (DefaultVertexBuffer*)(pVertexBuffer);
		auto shaderDefine = make_shared<DefaultShaderDefine>();
		shaderDefine->SetShaderDefine(pDefaultBuffer->Layout());
		//shaderDefine->SetUseGBuffer(true);
		return ShaderManager::Instance()->FindOrNew(shaderDefine);
	}
	else
	{
		assert(0);
	}

	return nullptr;
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
}