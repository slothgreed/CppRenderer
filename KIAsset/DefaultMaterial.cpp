namespace KI
{
namespace Asset
{
DefaultMaterial::DefaultMaterial()
{
	auto pVertexUniform = make_shared<DefaultVertexUniform>();
	auto pFragUniform = make_shared<DefaultFragUniform>();
	m_pUniform = make_shared<UniformSet>(pVertexUniform, pFragUniform);
}

DefaultMaterial::~DefaultMaterial()
{

}

void DefaultMaterial::AddTexture(shared_ptr<Texture> texture)
{
	if (m_pUniform->Frag()->Type() != SHADER_TYPE::SHADER_TYPE_DEFAULT)
	{
		assert(0);
		return;
	}

	auto uniform = static_pointer_cast<DefaultFragUniform>(m_pUniform->Frag());
	uniform->SetTexture(texture);
}

void DefaultMaterial::SetFixColor(vec4 color)
{
	if (m_pUniform->Vertex()->Type() != SHADER_TYPE::SHADER_TYPE_DEFAULT)
	{
		assert(0);
		return;
	}

	auto uniform = static_pointer_cast<DefaultVertexUniform>(m_pUniform->Vertex());
	uniform->SetFixColor(color);
}

void DefaultMaterial::VisibleNormal(bool visible)
{
	if (m_pUniform->Vertex()->Type() != SHADER_TYPE::SHADER_TYPE_DEFAULT)
	{
		assert(0);
		return;
	}

	auto uniform = static_pointer_cast<DefaultVertexUniform>(m_pUniform->Vertex());
	uniform->VisibleNormal(visible);

	m_bReCompileShader = true;
}

void DefaultMaterial::CompileShader(IVertexBuffer* pVertexBuffer)
{
	if (pVertexBuffer->Type() == VERTEX_BUFFER_TYPE::VERTEX_BUFFER_TYPE_DEFAULT)
	{
		auto pDefaultBuffer = (DefaultVertexBuffer*)(pVertexBuffer);
		auto pBuildInfo = make_shared<IShaderBuildInfo>(SHADER_TYPE_DEFAULT);
		auto pVertexCode = make_shared<DefaultVertexCode>();
		pVertexCode->SetShaderDefine(pDefaultBuffer->Layout());
		auto uniform = static_pointer_cast<DefaultVertexUniform>(m_pUniform->Vertex());
		pVertexCode->SetViewNormal(uniform->VisibleNormal());
		pBuildInfo->SetVertexCode(pVertexCode);
		auto pFragCode = make_shared<DefaultFragCode>();
		pFragCode->SetShaderDefine(pDefaultBuffer->Layout());
		pBuildInfo->SetFragCode(pFragCode);
		SetShader(ShaderManager::Instance()->FindOrNew(pBuildInfo));
	}
	else
	{
		assert(0);
	}
}

void DefaultMaterial::Bind(shared_ptr<IShader> pShader)
{
	pShader->Bind(m_pUniform);
}

void DefaultMaterial::UnBind(shared_ptr<IShader> pShader)
{
	pShader->UnBind(m_pUniform);
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