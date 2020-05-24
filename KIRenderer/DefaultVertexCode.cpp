namespace KI
{
namespace Renderer
{

DefaultVertexCode::DefaultVertexCode(VERTEX_LAYOUT layout)
	:DefaultVertexCode(
		string(SHADER_DIRECTORY) +
		string(SHADER_DEFAULT) +
		string(SHADER_EXT_VERTEX))
{
	SetShaderDefine(layout);
}

DefaultVertexCode::DefaultVertexCode(IVertexBuffer* pVertexBuffer)
	:DefaultVertexCode(
		string(SHADER_DIRECTORY) +
		string(SHADER_DEFAULT) +
		string(SHADER_EXT_VERTEX))
{
	auto pDefault = dynamic_cast<DefaultVertexBuffer*>(pVertexBuffer);
	if (pDefault != NULL)
	{
		SetShaderDefine(pDefault->Layout());
	}
}


DefaultVertexCode::DefaultVertexCode(const string& shaderCode)
	:IShaderCode(shaderCode)
{
	m_outNormal = false;
	m_outColor = false;
	m_planePosition = false;
	m_outTexcoord = false;
	m_outInstance = false;
}


DefaultVertexCode::~DefaultVertexCode()
{
}

void DefaultVertexCode::Initialize(GLuint programId)
{
}
void DefaultVertexCode::GetDefineCode(string& code)
{
	if (m_outNormal) {
		code += OUT_NORMAL;
	}

	if (m_outColor) {
		code += OUT_COLOR;
	}

	if (m_outTexcoord) {
		code += OUT_TEXCOORD;
	}

	if (m_outInstance) {
		code += OUT_INSTANCE;
	}
}

bool DefaultVertexCode::Compare(IShaderCode* pShaderCode)
{
	auto pCode = dynamic_cast<DefaultVertexCode*>(pShaderCode);
	if (pCode == nullptr)
	{
		return false;
	}

	if (m_outNormal == pCode->m_outNormal &&
		m_outColor == pCode->m_outColor &&
		m_outTexcoord == pCode->m_outTexcoord &&
		m_outInstance == pCode->m_outInstance &&
		m_outInstance == pCode->m_outInstance &&
		m_planePosition == pCode->m_planePosition)
	{
		return true;
	}

	return false;
}

void DefaultVertexCode::GetIncludeCode(vector<shared_ptr<IShaderCode>>& pShaderCodes)
{
	bool findShaderCommon = false;
	bool findShaderStruct = false;
	for (int i = 0; i < pShaderCodes.size(); i++)
	{
		if (typeid(pShaderCodes[i].get()).before(typeid(ShaderCommon*)))
		{
			findShaderCommon = true;
		}

		if (typeid(pShaderCodes[i].get()).before(typeid(ShaderStruct*)))
		{
			findShaderStruct = true;
		}
	}

	if (findShaderCommon == false)
	{
		pShaderCodes.push_back(make_shared<ShaderCommon>());
	}

	if (findShaderStruct == false)
	{
		pShaderCodes.push_back(make_shared<ShaderStruct>());
	}

}

shared_ptr<IShaderCode> DefaultVertexCode::GetVertexBufferCode(shared_ptr<IVertexBuffer> pVertexBuffer)
{
	auto pCode =  make_shared<DefaultVBOCode>(pVertexBuffer.get());
	pCode->SetPlanePosition(m_planePosition);

	return pCode;
}

void DefaultVertexCode::Bind(shared_ptr<IShaderChunk> pShaderChunk)
{

}

void DefaultVertexCode::UnBind(shared_ptr<IShaderChunk> pShaderChunk)
{

}

void DefaultVertexCode::SetShaderDefine(VERTEX_LAYOUT layout)
{
	if (layout & VERTEX_LAYOUT_NORMAL)
	{
		m_outNormal = true;
	}

	if (layout & VERTEX_LAYOUT_COLOR)
	{
		m_outColor = true;
	}

	if (layout & VERTEX_LAYOUT_TEXCOORD)
	{
		m_outTexcoord = true;
	}

	if (layout & VERTEX_LAYOUT_INSTANCE_MATRIX0 ||
		layout & VERTEX_LAYOUT_INSTANCE_MATRIX1 ||
		layout & VERTEX_LAYOUT_INSTANCE_MATRIX2 ||
		layout & VERTEX_LAYOUT_INSTANCE_MATRIX3)
	{
		m_outInstance = true;
	}
}
}
}


