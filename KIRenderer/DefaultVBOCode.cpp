namespace KI
{
namespace Renderer
{

DefaultVBOCode::DefaultVBOCode(IVertexBuffer* pVertexBuffer)
	:IShaderCode(
		string(SHADER_DIRECTORY) +
		string(SHADER_DEFAULT) +
		string(SHADER_EXT_VBO))
{

	m_inNormal = false;
	m_inColor = false;
	m_inTexcoord = false;
	m_inInstance = false;
	m_planePosition = false;

	auto pDefault = dynamic_cast<DefaultVertexBuffer*>(pVertexBuffer);
	if (pDefault != nullptr)
	{
		SetShaderDefine(pDefault->Layout());
	}
}

DefaultVBOCode::~DefaultVBOCode()
{
}

void DefaultVBOCode::GetDefineCode(string& code)
{
	if (m_planePosition){
		code += OUT_PLANE_POSITION;
	}

	if (m_inNormal) {
		code += IN_NORMAL;
	}
	if (m_inColor) {
		code += IN_COLOR;
	}

	if (m_inTexcoord) {
		code += IN_TEXCOORD;
	}

	if (m_inInstance) {
		code += IN_INSTANCE;
	}
}

bool DefaultVBOCode::Compare(IShaderCode* pShaderCode)
{
	auto pCode = dynamic_cast<DefaultVBOCode*>(pShaderCode);
	if (pCode == nullptr)
	{
		return false;
	}

	if (m_inNormal		== pCode->m_inNormal &&
		m_inColor		== pCode->m_inColor &&
		m_inTexcoord	== pCode->m_inTexcoord &&
		m_inInstance	== pCode->m_inInstance &&
		m_planePosition == pCode->m_planePosition)
	{
		return true;
	}

	return false;
}

void DefaultVBOCode::GetIncludeCode(vector<shared_ptr<IShaderCode>>& pShaderCodes)
{
}

void DefaultVBOCode::Bind(shared_ptr<IShaderChunk> pShaderChunk)
{

}

void DefaultVBOCode::UnBind(shared_ptr<IShaderChunk> pShaderChunk)
{

}

void DefaultVBOCode::SetShaderDefine(VERTEX_LAYOUT layout)
{
	if (layout & VERTEX_LAYOUT_NORMAL)
	{
		m_inNormal = true;
	}

	if (layout & VERTEX_LAYOUT_COLOR)
	{
		m_inColor = true;
	}

	if (layout & VERTEX_LAYOUT_TEXCOORD)
	{
		m_inTexcoord = true;
	}

	if (layout & VERTEX_LAYOUT_INSTANCE_MATRIX0 ||
		layout & VERTEX_LAYOUT_INSTANCE_MATRIX1 ||
		layout & VERTEX_LAYOUT_INSTANCE_MATRIX2 ||
		layout & VERTEX_LAYOUT_INSTANCE_MATRIX3)
	{
		m_inInstance = true;
	}
}
}
}


