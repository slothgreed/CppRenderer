#define OUT_PLANE_POSITION	"#define OUT_PLANE_POSITION\n"
#define OUT_WORLD_POSITION	"#define OUT_WORLD_POSITION\n"

#define OUT_GL_PLANE_POSITION	"#define OUT_GL_PLANE_POSITION\n"
#define OUT_GL_WORLD_POSITION	"#define OUT_GL_WORLD_POSITION\n"
namespace KI
{
namespace ShaderLib
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
	m_planeGlPosition = false;
	m_worldGlPosition = false;
	m_planeOutPosition = false;
	m_worldOutPosition = false;
	
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
	if (m_planeGlPosition){
		code += OUT_GL_PLANE_POSITION;
	}
	
	if (m_worldGlPosition){
		code += OUT_GL_WORLD_POSITION;
	}

	if (m_planeOutPosition) {
		code += OUT_PLANE_POSITION;
	}

	if (m_worldOutPosition) {
		code += OUT_WORLD_POSITION;
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
		m_planeGlPosition == pCode->m_planeGlPosition &&
		m_worldGlPosition == pCode->m_worldGlPosition &&
		m_planeOutPosition == pCode->m_planeOutPosition &&
		m_worldOutPosition == pCode->m_worldOutPosition)
	{
		return true;
	}

	return false;
}

void DefaultVBOCode::GetIncludeCode(vector<shared_ptr<IShaderCode>>& pShaderCodes)
{
}

void DefaultVBOCode::Bind(shared_ptr<IShaderChunk> pShaderChunk,shared_ptr<IUniformStorage> pUniform)
{

}

void DefaultVBOCode::UnBind(shared_ptr<IShaderChunk> pShaderChunk,shared_ptr<IUniformStorage> pUniform)
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


