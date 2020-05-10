namespace KI
{
namespace Asset
{
DefaultShaderPass::DefaultShaderPass()
{
	auto pVertexUniform = make_shared<DefaultVertexUniform>();
	auto pFragUniform = make_shared<DefaultFragUniform>();
	GetUniform()->Set(pVertexUniform, pFragUniform);
	SetMaterial(make_shared<BasicMaterial>());
}

DefaultShaderPass::DefaultShaderPass(shared_ptr<IMaterial> pMaterial)
{
	auto pVertexUniform = make_shared<DefaultVertexUniform>();
	auto pFragUniform = make_shared<DefaultFragUniform>();
	GetUniform()->Set(pVertexUniform, pFragUniform);
	SetMaterial(pMaterial);
}


DefaultShaderPass::~DefaultShaderPass()
{

}

//void DefaultShaderPass::AddTexture(shared_ptr<Texture> texture)
//{
//	if (GetUniform()->Frag()->Type() != SHADER_TYPE::SHADER_TYPE_DEFAULT)
//	{
//		assert(0);
//		return;
//	}
//
//	auto uniform = static_pointer_cast<DefaultFragUniform>(GetUniform()->Frag());
//	uniform->SetTexture(texture);
//}
//
//void DefaultShaderPass::SetFixColor(const vec4& color)
//{
//	if (GetUniform()->Vertex()->Type() != SHADER_TYPE::SHADER_TYPE_DEFAULT)
//	{
//		assert(0);
//		return;
//	}
//
//	auto uniform = static_pointer_cast<DefaultVertexUniform>(GetUniform()->Vertex());
//	uniform->SetFixColor(color);
//}
//
//void DefaultShaderPass::VisibleNormal(bool visible)
//{
//	if (GetUniform()->Vertex()->Type() != SHADER_TYPE::SHADER_TYPE_DEFAULT)
//	{
//		assert(0);
//		return;
//	}
//
//	auto uniform = static_pointer_cast<DefaultVertexUniform>(GetUniform()->Vertex());
//	uniform->VisibleNormal(visible);
//
//	m_bReCompileShader = true;
//}

void DefaultShaderPass::CompileShader(IVertexBuffer* pVertexBuffer)
{
	if (pVertexBuffer->Type() == VERTEX_BUFFER_TYPE::VERTEX_BUFFER_TYPE_DEFAULT)
	{
		auto pDefaultBuffer = (DefaultVertexBuffer*)(pVertexBuffer);
		auto pBuildInfo = make_shared<IShaderBuildInfo>(SHADER_TYPE_DEFAULT);
		auto pVertexCode = make_shared<DefaultVertexCode>();
		pVertexCode->SetShaderDefine(pDefaultBuffer->Layout());
		auto uniform = static_pointer_cast<DefaultVertexUniform>(GetUniform()->Vertex());
		pBuildInfo->SetVertexCode(pVertexCode);
		auto pFragCode = make_shared<DefaultFragCode>();
		pFragCode->SetShaderDefine(pDefaultBuffer->Layout());
		pBuildInfo->SetFragCode(pFragCode);
		pBuildInfo->AddEmbeddedCode(GetMaterial());
		SetShader(ShaderManager::Instance()->FindOrNew(pBuildInfo));
	}
	else
	{
		assert(0);
	}
}

bool DefaultShaderPass::Compare(const IShaderPass& shaderPass)
{
	if (shaderPass.Type() == SHADERPASS_TYPE_DEFAULT)
	{
		assert(0);
		// todo : compare;
	}

	return false;
}
}
}