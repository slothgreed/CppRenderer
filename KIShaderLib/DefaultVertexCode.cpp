
#define OUT_POSITION		"#define OUT_POSITION\n"
#define OUT_NORMAL			"#define OUT_NORMAL\n"
#define OUT_COLOR			"#define OUT_COLOR\n"
#define OUT_TEXCOORD		"#define OUT_TEXCOORD\n"
#define OUT_TEXTURE0		"#define OUT_TEXTURE0\n"
#define OUT_INSTANCE		"#define OUT_INSTANCE\n"


namespace KI
{
namespace ShaderLib
{

DefaultVertexCode::DefaultVertexCode(VERTEX_LAYOUT layout)
	:DefaultVertexCode(
		string(SHADER_DIRECTORY) +
		string(SHADER_DEFAULT) +
		string(SHADER_EXT_VERTEX))
{
	SetShaderDefine(layout);
}


DefaultVertexCode::DefaultVertexCode(const string& shaderCode)
	:IShaderCode(shaderCode)
{
	m_outPosition = false;
	m_outNormal = false;
	m_outColor = false;
	m_planeGlPosition = false;
	m_worldGlPosition = false;
	m_planeOutPosition = false;
	m_worldOutPosition = false;
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
	if (m_outPosition) {
		code += OUT_POSITION;
	}
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

	if (m_outPosition == pCode->m_outPosition &&
		m_outNormal == pCode->m_outNormal &&
		m_outColor == pCode->m_outColor &&
		m_outTexcoord == pCode->m_outTexcoord &&
		m_outInstance == pCode->m_outInstance &&
		m_planeGlPosition == pCode->m_planeGlPosition &&
		m_worldGlPosition == pCode->m_worldGlPosition &&
		m_planeOutPosition == pCode->m_planeOutPosition &&
		m_worldOutPosition == pCode->m_worldOutPosition)
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

shared_ptr<IShaderCode> DefaultVertexCode::GetVertexBufferCode(shared_ptr<VertexBuffer> pVertexBuffer)
{
	auto pCode =  make_shared<DefaultVBOCode>(pVertexBuffer.get());
	pCode->SetPlaneGLPosition(m_planeGlPosition);
	pCode->SetWorldGLPosition(m_worldGlPosition);
	pCode->SetPlaneOutPosition(m_planeOutPosition);
	pCode->SetWorldOutPosition(m_worldOutPosition);

	return pCode;
}

void DefaultVertexCode::Bind(shared_ptr<IShaderChunk> pShaderChunk,shared_ptr<IUniformStorage> pUniform)
{

}

void DefaultVertexCode::UnBind(shared_ptr<IShaderChunk> pShaderChunk,shared_ptr<IUniformStorage> pUniform)
{

}

void DefaultVertexCode::SetShaderDefine(VERTEX_LAYOUT layout)
{
	if (layout & VERTEX_LAYOUT_POSITION) 
	{
		m_outPosition = true;
	}
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


